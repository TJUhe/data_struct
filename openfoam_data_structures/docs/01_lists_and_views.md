# 01. UList 与 List：OpenFOAM 的数组地基

OpenFOAM 里最常见的数据结构不是 STL 容器，而是 `UList<T>`、`List<T>`、`DynamicList<T>`、`FixedList<T, N>` 这一组列表类型。理解它们，后面的 `Field`、`labelList`、`scalarField`、`faceList` 都会顺起来。

## 先把问题翻译成熟悉语言

普通 C++ 里你可能会用：

```cpp
std::span<T>      // 非拥有视图
std::vector<T>    // 拥有连续数组
std::array<T, N>  // 固定长度数组
```

OpenFOAM 里的大致对应关系是：

| 普通概念 | OpenFOAM 类型 | 重点 |
| --- | --- | --- |
| 连续内存视图 | `UList<T>` | 只保存 `size_` 和 `T*`，不负责释放 |
| 拥有型数组 | `List<T>` | 继承 `UList<T>`，负责分配和释放 |
| 可增长数组 | `DynamicList<T>` | 有容量概念，适合增量收集 |
| 固定长度数组 | `FixedList<T, N>` | 小向量、小张量、三维索引常见 |

## UList：只有窗口，没有房子

源码：`src/OpenFOAM/containers/Lists/UList/UList.H`

`UList<T>` 的核心成员非常朴素：

```cpp
label size_;
T* __restrict__ v_;
```

这意味着它像一个窗口：知道从哪里开始、长度是多少，但不拥有这块内存。这样做有几个好处：

- 可以把已有数组、子区间、字段内部数据都统一暴露成列表接口。
- 避免为了传参创建临时 `List`。
- 在调试构建里可以集中做边界检查。

注意 `UList` 删除了默认赋值。源码注释解释了原因：对一个非拥有视图赋值，到底应该复制指针还是复制元素，很容易含混。OpenFOAM 选择让调用者显式表达浅拷贝或深拷贝语义。

## List：拥有内存的 UList

源码：`src/OpenFOAM/containers/Lists/List/List.H`

`List<T>` 继承 `UList<T>`，但负责分配 free-store 上的存储。它常被 typedef 成领域类型：

```text
labelList  = List<label>
scalarList = List<scalar>
pointField = Field<point>，而 Field 又继承 List<Type>
```

关键设计点是：算法接口可以尽量接收 `UList<T>`，需要持久保存数据时再用 `List<T>`。这和“函数参数用 span，成员变量用 vector”的现代 C++ 风格很接近。

## DynamicList：收集阶段使用

源码：`src/OpenFOAM/containers/Lists/DynamicList/DynamicList.H`

网格读取、拓扑构造、邻接关系生成时，经常不知道最后有多少元素。`DynamicList<T>` 负责动态增长；当数据稳定后，很多代码会转成 `List<T>` 或直接交给后续结构使用。

一个常见阅读姿势：

```text
DynamicList 收集候选元素
  -> List/labelList 固化
  -> UList 接口传给算法
```

## 为什么不用 std::vector 一把梭

OpenFOAM 是长期演进的大型 C++ 代码库。它的容器承担的不只是存储，还要和这些机制配合：

- OpenFOAM 自己的 `label`、`word`、I/O stream 和错误处理。
- 大量历史接口、模板字段运算和并行通信例程。
- 对边界检查、浅/深拷贝、临时对象生命周期的显式控制。
- 字段表达式里尽量避免不必要的数组复制。

所以这里的学习重点不是“它比 STL 更好”，而是观察一个工业库如何围绕自己的数值计算需求定制容器。

## 读源码时抓这几处

| 文件 | 读什么 |
| --- | --- |
| `UList.H` | `size_`、`v_`、构造函数、下标访问 |
| `UListI.H` | inline 的 `operator[]`、`begin/end`、`fcIndex/rcIndex` |
| `List.H` | 构造、拷贝、移动、`setSize` |
| `List.C` | 分配、释放、重新分配 |
| `DynamicList.H` | capacity、append、shrinkStorage |

## 小结

`UList` 和 `List` 是 OpenFOAM 数据结构体系的第一层：一个表达“如何看一段连续数据”，一个表达“谁拥有这段连续数据”。把这层分清，后面看到 `Field`、`SubField`、`labelUList`、`faceList` 时就不会迷路。
