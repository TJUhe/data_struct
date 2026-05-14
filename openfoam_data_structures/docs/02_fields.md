# 02. Field<Type>：从数组到数值场

`Field<Type>` 是 OpenFOAM 数值数据的基础容器。它看起来像数组，但承担了更多职责：参与场运算、支持临时对象复用、支持分量访问和 OpenFOAM I/O。

源码入口：`src/OpenFOAM/fields/Field/Field.H`

## Field 继承了什么

`Field<Type>` 的声明很能说明它的定位：

```cpp
class Field
:
    public tmp<Field<Type>>::refCount,
    public List<Type>
```

这句话可以拆成两层：

- `public List<Type>`：内部数据仍然是连续数组。
- `public tmp<Field<Type>>::refCount`：字段表达式产生临时对象时，可以被 `tmp<T>` 管理引用计数和释放。

所以 `scalarField`、`vectorField` 等类型，本质上都是“带数值语义的连续数组”。

## Type 参数为什么重要

OpenFOAM 的字段不是只存 `double`。常见 `Type` 包括：

| Type | 典型别名 | 含义 |
| --- | --- | --- |
| `scalar` | `scalarField` | 标量场 |
| `vector` | `vectorField` | 三维向量场 |
| `tensor` | `tensorField` | 张量场 |
| `label` | `labelField` | 整数索引场 |

`Field<Type>` 通过 `pTraits<Type>` 获得分量类型，例如 `vector` 的分量是 `scalar`。这让同一套模板函数可以处理标量、向量和张量。

## FieldFunctions：数组循环被包装成场运算

源码：

- `src/OpenFOAM/fields/Field/FieldFunctions.H`
- `src/OpenFOAM/fields/Field/FieldFunctions.C`
- `src/OpenFOAM/fields/Field/FieldFunctionsM.H`

在普通数据结构课程里，数组相加可能写成：

```cpp
for (label i = 0; i < a.size(); ++i)
{
    c[i] = a[i] + b[i];
}
```

OpenFOAM 把这些循环包装成字段函数和运算符，使物理方程代码更接近数学表达。你在求解器里看到的 `mag(U)`、`rho*U`、`fvc::grad(p)`，底层都会落到字段大小检查、循环、临时对象管理和边界处理上。

## SubField：不复制的子区间

源码：`src/OpenFOAM/fields/Field/SubField.H`

`SubField<Type>` 是 `Field` 世界里的子视图。它复用 `UList` 的思想，让算法可以处理一段连续区间而不复制数据。

这在边界 patch、局部计算、映射和通信中很常见：你需要对一段数据操作，但不想为了“看一眼”就分配新数组。

## tmp<Field<Type>>：表达式临时值的关键

字段运算很容易产生中间结果：

```text
a + b + c
```

如果每一步都深拷贝大型场，成本会非常高。`Field` 继承 `tmp<...>::refCount`，配合 `tmp<Field<Type>>`，让 OpenFOAM 能在很多场景中转移、复用或延迟释放临时对象。第 06 章会专门讲这个生命周期设计。

## 读源码时抓这几处

| 文件 | 读什么 |
| --- | --- |
| `Field.H` | 继承关系、构造函数、`cmptType` |
| `Field.C` | 构造、映射、赋值 |
| `FieldFunctions.H` | 常见函数声明 |
| `FieldFunctionsM.H` | 宏如何生成重复的场运算代码 |
| `SubField.H` | 子字段如何复用父字段存储 |

## 小结

`Field<Type>` 是 OpenFOAM 从“数据结构”走向“数值计算语言”的第一步。它仍然是连续数组，但已经带上类型分量、临时对象、数学运算和 I/O 语义。
