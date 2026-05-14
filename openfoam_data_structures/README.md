# OpenFOAMDataStructuresGuide

这是一个面向 C++/CFD 学习者的 OpenFOAM 源码阅读教程。主题不是重新实现数据结构，而是观察 OpenFOAM-dev 怎样把数组视图、拥有型列表、字段、网格拓扑、哈希表、对象注册表和临时对象管理组合成一套可扩展的 CFD 基础设施。

参考源码仓库：

- GitHub: <https://github.com/OpenFOAM/OpenFOAM-dev>
- 本教程分析版本：`OpenFOAM-dev` commit `5a49d53b`
- 主要源码目录：`src/OpenFOAM`、`src/finiteVolume`

## 你会学到什么

1. `UList` 和 `List` 为什么分成非拥有视图和拥有型数组。
2. `Field<Type>` 如何把数值数组提升为可参与场运算的基础类型。
3. `GeometricField` 怎样把内部场、边界场、量纲和网格位置绑在一起。
4. `polyMesh` 如何用点、面、owner/neighbour 和边界 patch 表示非结构网格。
5. `HashTable`、`dictionary`、`objectRegistry` 如何支撑运行时查找和 I/O。
6. `autoPtr`、`tmp`、`PtrList` 等类型怎样表达所有权、临时值和多态对象集合。
7. 如何把普通数据结构课程里的数组、哈希表、图和生命周期问题迁移到 OpenFOAM 源码阅读中。

## 建议学习路线

1. 先读 [01_lists_and_views.md](docs/01_lists_and_views.md)，理解 `UList`/`List` 的分工。
2. 再读 [02_fields.md](docs/02_fields.md)，把 `Field<Type>` 和场运算看成数值数组的升级版。
3. 读 [03_geometric_field.md](docs/03_geometric_field.md)，理解一个 `volScalarField` 为什么不只是数组。
4. 读 [04_poly_mesh.md](docs/04_poly_mesh.md)，用图结构眼光看 polyMesh。
5. 读 [05_hash_registry_dictionary.md](docs/05_hash_registry_dictionary.md)，掌握名字到对象、名字到配置的映射。
6. 读 [06_ownership_and_tmp.md](docs/06_ownership_and_tmp.md)，看 OpenFOAM 如何降低大字段拷贝成本。
7. 最后读 [99_source_index.md](docs/99_source_index.md)，按源码路径继续扩展。

## 目录结构

```text
openfoam_data_structures/
├── README.md
├── docs/
│   ├── 01_lists_and_views.md
│   ├── 02_fields.md
│   ├── 03_geometric_field.md
│   ├── 04_poly_mesh.md
│   ├── 05_hash_registry_dictionary.md
│   ├── 06_ownership_and_tmp.md
│   └── 99_source_index.md
└── exercises/
    └── README.md
```

## 核心源码速查

| 主题 | OpenFOAM 源码路径 |
| --- | --- |
| 非拥有连续数组视图 | `src/OpenFOAM/containers/Lists/UList/UList.H` |
| 拥有型连续数组 | `src/OpenFOAM/containers/Lists/List/List.H` |
| 可增长数组 | `src/OpenFOAM/containers/Lists/DynamicList/DynamicList.H` |
| 基础数值场 | `src/OpenFOAM/fields/Field/Field.H` |
| 几何场 | `src/finiteVolume/fields/GeometricFields/GeometricField/GeometricField.H` |
| 体场/面场别名 | `src/finiteVolume/fields/volFields/volFields.H`、`surfaceFields.H` |
| 非结构网格 | `src/OpenFOAM/meshes/polyMesh/polyMesh.H` |
| 边界 patch | `src/OpenFOAM/meshes/polyMesh/polyPatches/polyPatch/polyPatch.H` |
| 哈希表 | `src/OpenFOAM/containers/HashTables/HashTable/HashTable.H` |
| 字典 | `src/OpenFOAM/db/dictionary/dictionary.H` |
| 对象注册表 | `src/OpenFOAM/db/objectRegistry/objectRegistry.H` |
| 智能指针 | `src/OpenFOAM/memory/autoPtr/autoPtr.H`、`src/OpenFOAM/memory/tmp/tmp.H` |

## 学习方法

每章都建议按同一个节奏读：

1. 先看“要解决的问题”，把它翻译成普通数据结构问题。
2. 再看 OpenFOAM 的类层次和关键成员。
3. 打开列出的源码路径，只读类声明、构造函数和核心访问函数。
4. 最后做练习，把概念画成自己的图。

OpenFOAM 源码有大量模板、宏和物理术语。读这个教程时不必一次吞下全部 CFD 背景，先抓住数据如何被组织、索引、查找和释放，后面的数值算法会变得清楚很多。
