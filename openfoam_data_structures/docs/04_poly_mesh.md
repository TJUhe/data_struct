# 04. polyMesh：把非结构网格看成图

`polyMesh` 是 OpenFOAM 网格拓扑的核心。它表示由任意多面体 cell 组成的非结构网格。用数据结构语言说，它是一张带几何坐标、面连接关系和边界分类的图。

源码入口：`src/OpenFOAM/meshes/polyMesh/polyMesh.H`

## 四个核心数组

`polyMesh` 里最关键的基础数据是：

```text
points_    : pointIOField
faces_     : faceCompactIOList
owner_     : labelIOList
neighbour_ : labelIOList
```

直觉如下：

- `points_` 保存所有顶点坐标。
- `faces_` 保存每个面由哪些 point 构成。
- `owner_[facei]` 保存该 face 所属的 owner cell。
- `neighbour_[facei]` 保存内部 face 另一侧的 neighbour cell。

对于边界 face，通常只有 owner，没有 neighbour。边界信息由 `polyBoundaryMesh` 和各类 `polyPatch` 管理。

## 用图来理解 owner/neighbour

在普通图算法里，cell 可以看成顶点，face 可以看成边：

```text
cell A -- face f -- cell B
```

`owner` 和 `neighbour` 就是 face 到两侧 cell 的邻接表。有限体积离散经常沿 face 遍历，所以这种表示非常直接：

```text
for each internal face:
    own = owner[facei]
    nei = neighbour[facei]
    在 own 与 nei 之间交换通量/梯度信息
```

这也是为什么 OpenFOAM 的很多矩阵结构和 face 循环紧密相关。

## polyMesh 继承 objectRegistry

`polyMesh` 的声明中有两个重要基类：

```text
objectRegistry
primitiveMesh
```

- `primitiveMesh` 提供基础拓扑查询。
- `objectRegistry` 让 mesh 成为字段和 mesh object 的注册中心。

这意味着一个 mesh 不只是几何数据，还像一个局部数据库：速度场、压力场、插值对象、缓存对象都可以按名字注册到它下面。

## 边界 patch 是分组视图

源码：

- `src/OpenFOAM/meshes/polyMesh/polyBoundaryMesh/polyBoundaryMesh.H`
- `src/OpenFOAM/meshes/polyMesh/polyPatches/polyPatch/polyPatch.H`

边界 patch 把连续的一段边界 face 归为一类，例如 inlet、outlet、wall。数据结构上，它像对 face 列表的一组命名区间：

```text
boundary
├── patch 0: name=inlet,  startFace=...
├── patch 1: name=outlet, startFace=...
└── patch 2: name=walls,  startFace=...
```

后续边界条件会按 patch 顺序挂接到这些区域上。

## 缓存与派生数据

网格有些数据可以从 primitives 推导出来，例如 cellFaces、pointCells、bounds、globalMeshData。OpenFOAM 不一定在构造时全部算好，而是按需缓存、在网格变化时清理。

读源码时如果看到 `mutable` 指针或 `clearOut`/`clearGeom` 之类函数，可以把它理解为：

```text
基础数据稳定保存
派生数据按需生成
网格移动或拓扑变化时失效
```

这是大型网格数据结构里非常重要的性能策略。

## 读源码时抓这几处

| 文件 | 读什么 |
| --- | --- |
| `polyMesh.H` | `points_`、`faces_`、`owner_`、`neighbour_` |
| `polyMeshIO.C` | 网格如何从文件读入 |
| `polyMeshClear.C` | 缓存如何清理 |
| `primitiveMesh.H` | 基础拓扑查询 |
| `polyPatch.H` | patch 的名字、类型和 face 区间 |

## 小结

`polyMesh` 的核心不是“存一堆几何”，而是把 CFD 离散最需要的邻接关系组织成高效数组。它把网格看成可 I/O、可查询、可缓存、可注册对象的图结构。
