# 05. HashTable、dictionary 与 objectRegistry

OpenFOAM 大量依赖“名字 -> 对象”与“名字 -> 配置”的查找。`HashTable`、`dictionary`、`objectRegistry` 是这一层的主角。

## HashTable：名字查找的底层容器

源码：`src/OpenFOAM/containers/HashTables/HashTable/HashTable.H`

OpenFOAM 的 `HashTable<T, Key, Hash>` 是通用哈希表。很多上层结构都建立在它之上：

```text
dictionary       : keyword -> entry
objectRegistry   : word -> regIOobject*
runtime selection: word -> constructor function pointer
```

普通数据结构课里的哈希表知识在这里直接适用：hash、bucket、冲突、插入、删除、查找、遍历。

## dictionary：case 文件的语法树

源码：`src/OpenFOAM/db/dictionary/dictionary.H`

OpenFOAM 的 case 文件看起来像配置文件：

```text
U
{
    type fixedValue;
    value uniform (1 0 0);
}
```

读入后会变成 `dictionary` 和 `entry` 对象。它不是简单的字符串 map，因为 entry 可能是：

- primitive entry：数字、word、vector、list。
- dictionary entry：嵌套字典。
- function entry：`#include`、`#codeStream` 等特殊入口。

所以 `dictionary` 更像一棵配置语法树，而不只是 `unordered_map<string, string>`。

## objectRegistry：运行时对象表

源码：`src/OpenFOAM/db/objectRegistry/objectRegistry.H`

`objectRegistry` 继承：

```text
regIOobject
HashTable<regIOobject*>
```

它负责把已经读入或生成的对象按名字登记起来。一个典型场景是：求解器创建 `volVectorField U` 后，其他模型可以从 mesh registry 中按名字找到它。

可以把它想成一个带层级的对象数据库：

```text
Time registry
└── mesh registry
    ├── U
    ├── p
    ├── phi
    └── turbulenceProperties
```

## registry 为什么和 mesh 绑在一起

第 04 章提到 `polyMesh` 继承 `objectRegistry`。这让每个 mesh 都能拥有自己的对象空间。多区域计算时，不同 region 可以有各自的 mesh、字段和模型，名字相同也不会混在一起。

这是一个很实用的数据结构选择：用树状 registry 划分命名空间，用哈希表做局部快速查找。

## 运行时选择表也是 HashTable

设计模式教程会细讲运行时选择表。这里只从数据结构看：

```text
word 类型名 -> 构造函数指针
```

例如 `Function1`、`fvPatchField`、`snGradScheme` 都会声明运行时选择表。用户在 dictionary 里写 `type linear;`，OpenFOAM 就用这个 word 去哈希表中找对应构造函数。

## 读源码时抓这几处

| 文件 | 读什么 |
| --- | --- |
| `HashTable.H` | 模板参数、插入、查找、迭代 |
| `dictionary.H` | lookup、subDict、entry 组织 |
| `entry.H` | primitive entry 与 dictionary entry 的共同接口 |
| `objectRegistry.H` | 继承 `HashTable<regIOobject*>` |
| `objectRegistryTemplates.C` | lookupObject 等模板查找函数 |

## 小结

OpenFOAM 的可配置性不是魔法，底层很大一部分就是哈希表：配置字典把文本变成结构化数据，对象注册表把名字变成对象指针，运行时选择表把类型名变成构造函数。
