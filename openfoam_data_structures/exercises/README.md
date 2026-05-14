# OpenFOAM 数据结构练习

这些练习不要求编译 OpenFOAM，重点是训练源码阅读和结构化表达。

## 练习 1：画出 UList 与 List 的所有权关系

阅读：

- `src/OpenFOAM/containers/Lists/UList/UList.H`
- `src/OpenFOAM/containers/Lists/List/List.H`

回答：

1. `UList<T>` 保存了哪些成员？
2. 为什么 `UList<T>` 不应该默认深拷贝？
3. `List<T>` 比 `UList<T>` 多承担了什么责任？

## 练习 2：追踪 scalarField

从 `scalarField.H` 出发，追踪它最终如何落到 `Field<scalar>` 和 `List<scalar>`。

建议画成：

```text
scalarField
  -> Field<scalar>
  -> List<scalar>
  -> UList<scalar>
```

## 练习 3：把 polyMesh 转成图模型

阅读 `polyMesh.H` 中的 `points_`、`faces_`、`owner_`、`neighbour_`。

用自己的话说明：

1. cell 如何通过 face 相邻？
2. 为什么边界 face 没有普通 neighbour？
3. 如果要遍历某个 cell 的相邻 cell，需要哪些派生结构或查询函数？

## 练习 4：查找对象注册路径

找一个求解器中创建 `volScalarField p` 或 `volVectorField U` 的代码片段，回答：

1. 字段对象的名字是什么？
2. 它属于哪个 mesh/objectRegistry？
3. 后续模型如何按名字查到它？

## 练习 5：解释 tmp 返回值

找一个返回 `tmp<...>` 的函数，例如有限体积离散函数或场函数。

回答：

1. 返回的对象可能是临时值还是已有引用？
2. 如果不用 `tmp`，最直接的实现会产生什么拷贝成本？
3. 调用方应该如何接收这个返回值？

## 练习 6：设计一个迷你 registry

不用 OpenFOAM，只用普通 C++ 设计一个迷你对象表：

```cpp
std::unordered_map<std::string, Base*>
```

再思考 OpenFOAM 为什么还需要：

- 对象 I/O 状态。
- 父子 registry。
- 类型安全的 lookup。
- 对象注册和注销生命周期。

写一页短文，把你的迷你版本和 `objectRegistry` 对照起来。
