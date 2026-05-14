# 03. GeometricField：带网格位置的字段

如果说 `Field<Type>` 是一段数值数组，那么 `GeometricField<Type, GeoMesh, PrimitiveField>` 就是在回答：这段数值位于哪里？它属于 cell、face 还是 point？边界怎么处理？量纲是什么？

源码入口：`src/finiteVolume/fields/GeometricFields/GeometricField/GeometricField.H`

## 一个 volScalarField 包了什么

OpenFOAM 中常见的 `volScalarField` 可以理解成：

```text
内部场 internalField
边界场 boundaryField
场源 sources
量纲 dimensions
IOobject 名字、时间目录、读写策略
mesh 引用
oldTime / prevIter 历史值
```

所以它不是 `std::vector<double>` 的别名，而是一个带物理位置、单位、边界条件和生命周期的对象。

## 类层次

`GeometricField` 继承：

```text
DimensionedField<Type, GeoMesh, PrimitiveField>
OldTimeField<GeometricField<...>>
```

并持有：

```text
Boundary boundaryField_
Sources sources_
mutable GeometricField* fieldPrevIterPtr_
```

可以这样理解：

- `DimensionedField` 管内部场、量纲和 mesh。
- `Boundary` 管每个 patch 上的边界字段。
- `OldTimeField` 管时间推进需要的历史字段。
- `fieldPrevIterPtr_` 服务于迭代过程中的欠松弛等操作。

## internalField 与 boundaryField

有限体积法中，cell 中心值和边界 patch 值经常一起出现，但它们不是同一段数据。

```text
volField
├── internal field: 每个 cell 一个值
└── boundary field:
    ├── inlet patch values
    ├── outlet patch values
    └── wall patch values
```

这就是为什么 `GeometricField` 需要同时继承内部场能力，又组合一个边界场对象。数据结构上，它是“主数组 + patch 数组集合”的组合。

## GeoMesh 参数在表达位置

`GeoMesh` 决定字段挂在哪里：

| 常见字段 | 位置 | 直觉 |
| --- | --- | --- |
| `volScalarField` | cell 体心 | 压力、温度、密度 |
| `volVectorField` | cell 体心 | 速度 |
| `surfaceScalarField` | face 面心 | 通量 |
| `pointScalarField` | point 顶点 | 后处理、插值结果 |

这比“数组长度是多少”更重要，因为数值离散操作必须知道字段和网格拓扑的关系。

## 边界场也是多态对象集合

每个 patch 的边界条件类型可能不同：

```text
inlet  -> fixedValue
outlet -> zeroGradient
wall   -> noSlip
```

这些 patch field 通过运行时选择表构造，存入边界字段集合。数据结构上它同时用了：

- 列表：按 patch 顺序保存。
- 多态：不同 patch 有不同派生类。
- 字典：从 case 文件读取 `type` 和参数。

这部分会在设计模式教程里从 Factory/Strategy 角度再讲一次。

## 读源码时抓这几处

| 文件 | 读什么 |
| --- | --- |
| `GeometricField.H` | typedef、继承、`boundaryField_` |
| `GeometricField.C` | 构造、读取、写出 |
| `GeometricBoundaryField.H` | patch field 列表如何组织 |
| `DimensionedField.H` | 量纲和内部场 |
| `OldTimeField.H` | 时间历史如何挂到字段上 |

## 小结

`GeometricField` 的核心思想是组合：连续数组提供数值存储，mesh 提供位置，boundary field 提供边界行为，dimension 提供物理单位，IOobject 提供持久化身份。它是 OpenFOAM “数据结构 + 物理语义”的代表。
