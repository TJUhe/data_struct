# 99. OpenFOAM 数据结构源码索引

本索引用于从教程跳回 OpenFOAM-dev 源码。路径基于 `OpenFOAM-dev` commit `5a49d53b`。

## 列表与数组

| 主题 | 路径 |
| --- | --- |
| `UList<T>` 非拥有数组视图 | `src/OpenFOAM/containers/Lists/UList/UList.H` |
| `List<T>` 拥有型数组 | `src/OpenFOAM/containers/Lists/List/List.H` |
| `DynamicList<T>` 可增长数组 | `src/OpenFOAM/containers/Lists/DynamicList/DynamicList.H` |
| `FixedList<T, N>` 固定长度数组 | `src/OpenFOAM/containers/Lists/FixedList/FixedList.H` |
| `SubList<T>` 子列表视图 | `src/OpenFOAM/containers/Lists/SubList/SubList.H` |
| `labelList` | `src/OpenFOAM/primitives/ints/lists/labelList.H` |
| `scalarList` | `src/OpenFOAM/primitives/Scalar/lists/scalarList.H` |

## 字段

| 主题 | 路径 |
| --- | --- |
| `Field<Type>` | `src/OpenFOAM/fields/Field/Field.H` |
| `SubField<Type>` | `src/OpenFOAM/fields/Field/SubField.H` |
| 字段函数 | `src/OpenFOAM/fields/Field/FieldFunctions.H` |
| 动态字段 | `src/OpenFOAM/fields/DynamicField/DynamicField.H` |
| 标量场别名 | `src/OpenFOAM/fields/scalarField/scalarField.H` |
| 向量场别名 | `src/OpenFOAM/fields/vectorField/vectorField.H` |

## 几何场与有限体积

| 主题 | 路径 |
| --- | --- |
| `GeometricField` | `src/finiteVolume/fields/GeometricFields/GeometricField/GeometricField.H` |
| `DimensionedField` | `src/finiteVolume/fields/DimensionedFields/DimensionedField/DimensionedField.H` |
| `GeometricBoundaryField` | `src/finiteVolume/fields/GeometricFields/GeometricField/GeometricBoundaryField.H` |
| `OldTimeField` | `src/finiteVolume/fields/OldTimeField/OldTimeField.H` |
| vol 字段别名 | `src/finiteVolume/fields/volFields/volFields.H` |
| surface 字段别名 | `src/finiteVolume/fields/surfaceFields/surfaceFields.H` |

## 网格

| 主题 | 路径 |
| --- | --- |
| `polyMesh` | `src/OpenFOAM/meshes/polyMesh/polyMesh.H` |
| `primitiveMesh` | `src/OpenFOAM/meshes/primitiveMesh/primitiveMesh.H` |
| `polyBoundaryMesh` | `src/OpenFOAM/meshes/polyMesh/polyBoundaryMesh/polyBoundaryMesh.H` |
| `polyPatch` | `src/OpenFOAM/meshes/polyMesh/polyPatches/polyPatch/polyPatch.H` |
| face 列表 | `src/OpenFOAM/meshes/meshShapes/face/faceList.H` |
| cell 列表 | `src/OpenFOAM/meshes/meshShapes/cell/cellList.H` |
| point field | `src/OpenFOAM/meshes/primitiveShapes/point/pointField.H` |

## 哈希、字典和注册表

| 主题 | 路径 |
| --- | --- |
| `HashTable` | `src/OpenFOAM/containers/HashTables/HashTable/HashTable.H` |
| `HashSet` | `src/OpenFOAM/containers/HashTables/HashSet/HashSet.H` |
| `Map` | `src/OpenFOAM/containers/HashTables/Map/Map.H` |
| `dictionary` | `src/OpenFOAM/db/dictionary/dictionary.H` |
| `entry` | `src/OpenFOAM/db/dictionary/entry/entry.H` |
| `objectRegistry` | `src/OpenFOAM/db/objectRegistry/objectRegistry.H` |
| `regIOobject` | `src/OpenFOAM/db/regIOobject/regIOobject.H` |
| `IOobject` | `src/OpenFOAM/db/IOobject/IOobject.H` |

## 所有权与临时对象

| 主题 | 路径 |
| --- | --- |
| `autoPtr` | `src/OpenFOAM/memory/autoPtr/autoPtr.H` |
| `tmp` | `src/OpenFOAM/memory/tmp/tmp.H` |
| `refCount` | `src/OpenFOAM/memory/refCount/refCount.H` |
| `PtrList` | `src/OpenFOAM/containers/Lists/PtrList/PtrList.H` |
| `UPtrList` | `src/OpenFOAM/containers/Lists/UPtrList/UPtrList.H` |

## 推荐源码阅读顺序

1. `UList.H` -> `List.H` -> `Field.H`
2. `DimensionedField.H` -> `GeometricField.H` -> `GeometricBoundaryField.H`
3. `polyMesh.H` -> `polyPatch.H` -> `primitiveMesh.H`
4. `HashTable.H` -> `dictionary.H` -> `objectRegistry.H`
5. `autoPtr.H` -> `tmp.H` -> 一个 `New.C` 工厂函数

读完这些，再进入具体求解器和离散格式时，会更容易区分“数值算法本身”和“支撑算法的数据结构”。
