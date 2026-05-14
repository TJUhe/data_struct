# 06. autoPtr、tmp 与多态对象集合

OpenFOAM 处理的是大型网格和大型字段。一次无意的深拷贝就可能带来明显成本。因此它有一套很有特色的所有权和临时对象类型：`autoPtr`、`tmp`、`PtrList`、`UPtrList` 等。

## autoPtr：独占所有权

源码：`src/OpenFOAM/memory/autoPtr/autoPtr.H`

`autoPtr<T>` 表达“这个指针由我负责释放”。它常出现在工厂函数返回值中：

```text
static autoPtr<Base> New(...);
```

运行时选择表根据字典创建派生类对象，再用 `autoPtr<Base>` 返回。调用者获得一个拥有对象生命周期的指针。

这和现代 C++ 的 `std::unique_ptr` 在意图上接近，但 OpenFOAM 保留了自己的接口和历史语义。

## tmp<T>：临时字段管理器

源码：`src/OpenFOAM/memory/tmp/tmp.H`

`tmp<T>` 是理解 OpenFOAM 字段表达式性能的关键。它可能持有：

```text
REUSABLE_TMP      可复用临时对象
NON_RESUSABLE_TMP 不可复用临时对象
CONST_REF         常量引用
```

它配合 `T` 中的 `refCount` 使用，让大型字段运算可以少复制、及时释放、必要时转移所有权。

比如一个离散操作返回 `tmp<volScalarField>`，意思是：这里有一个可能很大的临时字段，请按 OpenFOAM 的规则接住它，不要随便复制。

## PtrList：拥有一组多态对象

源码：`src/OpenFOAM/containers/Lists/PtrList/PtrList.H`

很多地方需要保存一组基类指针，但每个元素实际类型不同。例如边界 patch field、模型列表、函数对象列表。这时会用 `PtrList<T>` 或相关类型。

可以把它理解成：

```text
List<T*> + 负责删除元素 + OpenFOAM I/O/克隆习惯
```

而 `UPtrList<T>` 更偏非拥有指针列表，类似 `UList` 和 `List` 的关系：一个看，一拥有。

## 所有权三问

读 OpenFOAM 源码时，遇到指针和列表可以先问三个问题：

1. 谁拥有对象？
2. 对象能不能多态删除？
3. 返回值是新对象、临时对象，还是已有对象的引用？

常见答案：

| 类型 | 表达 |
| --- | --- |
| `autoPtr<T>` | 独占拥有一个多态对象 |
| `tmp<T>` | 临时值或常量引用，常用于字段表达式 |
| `PtrList<T>` | 拥有一组指针元素 |
| `UPtrList<T>` | 非拥有指针视图 |
| `refPtr<T>`、`refCount` | 引用计数语义，具体看对应类型 |

## 为什么这也是数据结构问题

生命周期管理和数据结构分不开。字段数组、边界条件对象、模型对象都不是孤立存在的：

- `GeometricField` 需要管理内部场和边界场。
- `objectRegistry` 保存对象指针，但对象也有注册/注销生命周期。
- 工厂函数创建派生类后必须把所有权交给调用者。
- 临时字段必须避免过早释放，也要避免长期占内存。

所以 OpenFOAM 的内存类型是“数据怎么活着”的数据结构。

## 读源码时抓这几处

| 文件 | 读什么 |
| --- | --- |
| `autoPtr.H` / `autoPtrI.H` | 构造、释放、转移 |
| `tmp.H` / `tmpI.H` | 三种状态、析构、`ptr()` |
| `PtrList.H` | 指针列表的拥有语义 |
| `UPtrList.H` | 非拥有指针列表 |
| `Field.H` | 为什么继承 `tmp<Field<Type>>::refCount` |

## 小结

`autoPtr` 和 `tmp` 让 OpenFOAM 在大量多态对象和大型字段表达式之间保持可控生命周期。读懂这些类型，就能少很多“这个对象到底什么时候释放”的困惑。
