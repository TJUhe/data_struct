# CppDataStructuresLab

这是一个面向 C++ 学习者的数据结构教程仓库。它的目标不是只给出 STL 用法，而是让你亲手实现常见数据结构，理解它们为什么这样设计，以及在什么场景下该选哪一个。

仓库远程名称可以继续叫 `data_struct`，但项目名使用 `CppDataStructuresLab`，读起来更像一个完整的练习实验室。

## 你会学到什么

1. 如何用 C++20 实现动态数组、链表、栈、队列、哈希表、树、堆、图和排序算法。
2. 如何分析时间复杂度和空间复杂度，而不是死记 `O(1)`、`O(n)`。
3. 如何用 CMake 管理多个小示例程序。
4. 如何在 VS Code 里选择章节目标、打断点、单步调试。
5. 如何把多个结构组合起来解决一个真实小问题，例如 LRU 缓存。

## 环境要求

- C++20 编译器：MSVC、Clang 或 GCC 都可以。
- CMake 3.20 或更高版本。
- Ninja。也可以把 `CMakePresets.json` 里的 generator 改成你本机已有的生成器。
- VS Code 推荐扩展：C/C++、CMake Tools。

Windows 上如果使用 Visual Studio Build Tools，可以直接使用仓库里的 Ninja/MSVC 辅助脚本；它会自动调用 `vswhere.exe` 查找 Visual Studio，并加载 `vcvars64.bat`。如果你的安装位置比较特殊，也可以手动设置环境变量 `VS_VCVARS64` 指向 `vcvars64.bat`。

## 快速开始

Windows + MSVC + Ninja 推荐：

```powershell
.\scripts\cmake_msvc_ninja.bat configure
.\scripts\cmake_msvc_ninja.bat build
.\scripts\cmake_msvc_ninja.bat test
```

如果你已经在 x64 Native Tools Command Prompt、Linux、macOS 或其他已配置好编译器的环境里，也可以直接使用 CMake preset：

```powershell
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

运行某一章示例：

```powershell
.\build\debug\bin\02_array_list.exe
.\build\debug\bin\08_graph.exe
```

Release 构建适合做简单性能观察：

```powershell
cmake --preset release
cmake --build --preset release
.\build\release\bin\01_complexity.exe
```

## VS Code 调试

1. 用 VS Code 打开本仓库根目录。
2. 安装推荐扩展。
3. 选择 CMake preset: `debug`。
4. 打开 "Run and Debug"。
5. 选择 `Debug current chapter target`。
6. 从弹出的列表里选择 `01_complexity` 到 `10_integrated_lru` 中任意一个目标。

VS Code 的默认构建任务会调用 [scripts/cmake_msvc_ninja.bat](scripts/cmake_msvc_ninja.bat)，因此在普通 VS Code 终端里也能加载 MSVC x64 环境后再执行 Ninja 构建。

如果你想单步观察动态数组扩容，可以调试 `02_array_list`，在 `include/ds/dynamic_array.hpp` 的 `reserve` 和 `insert` 函数里打断点。

## 目录结构

```text
.
├── CMakeLists.txt
├── CMakePresets.json
├── include/ds/                 # 数据结构实现
├── examples/                   # 每章可运行示例
├── docs/                       # 详细教程
├── exercises/                  # 练习题
├── scripts/                    # Windows MSVC + Ninja 辅助脚本
├── tests/                      # smoke tests
└── .vscode/                    # VS Code 构建和调试配置
```

## 学习路线

建议按这个顺序学习：

1. 复杂度：先学会估算代码随输入规模增长的速度。
2. 动态数组：理解连续内存、扩容、随机访问、插入删除成本。
3. 链表：理解指针、节点、局部修改和缓存不友好。
4. 栈与队列：理解受限访问带来的算法表达能力。
5. 哈希表：理解哈希函数、冲突、负载因子和扩容。
6. 树：理解层次结构、BST 搜索性质和遍历。
7. 堆：理解优先级队列和局部有序。
8. 图：理解邻接表、BFS、DFS、最短路。
9. 排序：比较插入排序、快速排序、归并排序。
10. 综合项目：用哈希表加链表实现 LRU 缓存。

## 每章文件

| 章节 | 示例目标 | 主要头文件 | 文档 |
| --- | --- | --- | --- |
| 01 | `01_complexity` | 无 | [docs/01_complexity.md](docs/01_complexity.md) |
| 02 | `02_array_list` | `dynamic_array.hpp` | [docs/02_array_list.md](docs/02_array_list.md) |
| 03 | `03_linked_list` | `linked_list.hpp` | [docs/03_linked_list.md](docs/03_linked_list.md) |
| 04 | `04_stack_queue` | `stack.hpp`, `queue.hpp` | [docs/04_stack_queue.md](docs/04_stack_queue.md) |
| 05 | `05_hash_table` | `hash_table.hpp` | [docs/05_hash_table.md](docs/05_hash_table.md) |
| 06 | `06_tree` | `binary_search_tree.hpp` | [docs/06_tree.md](docs/06_tree.md) |
| 07 | `07_heap_priority_queue` | `binary_heap.hpp` | [docs/07_heap_priority_queue.md](docs/07_heap_priority_queue.md) |
| 08 | `08_graph` | `graph.hpp` | [docs/08_graph.md](docs/08_graph.md) |
| 09 | `09_sorting` | `sorting.hpp` | [docs/09_sorting.md](docs/09_sorting.md) |
| 10 | `10_integrated_lru` | `lru_cache.hpp` | [docs/10_integrated_lru.md](docs/10_integrated_lru.md) |

## 图解索引

每章教程都已经嵌入 SVG 辅助图，图片源码位于 [docs/images](docs/images)：

| 章节 | 图解 |
| --- | --- |
| 复杂度 | [增长曲线](docs/images/01_complexity.svg) |
| 动态数组 | [扩容与连续内存](docs/images/02_array_list.svg) |
| 链表 | [节点与 next 指针](docs/images/03_linked_list.svg) |
| 栈与队列 | [LIFO/FIFO 访问规则](docs/images/04_stack_queue.svg) |
| 哈希表 | [桶与拉链法](docs/images/05_hash_table.svg) |
| 二叉搜索树 | [左右子树顺序关系](docs/images/06_tree.svg) |
| 堆 | [树形结构与数组映射](docs/images/07_heap_priority_queue.svg) |
| 图 | [顶点、边和权重](docs/images/08_graph.svg) |
| 排序 | [插入/快排/归并思路](docs/images/09_sorting.svg) |
| LRU | [哈希表加链表](docs/images/10_integrated_lru.svg) |

## 学习方法

每章推荐用同一个节奏：

1. 先读 `docs/xx_*.md`，只抓核心问题：这个结构解决了什么痛点。
2. 运行对应 `examples/xx_*/main.cpp`。
3. 在核心函数打断点，观察变量如何变化。
4. 修改示例输入，让边界情况出现：空结构、一个元素、重复元素、扩容、删除不存在的元素。
5. 做 `exercises/README.md` 里的练习。
6. 最后再回头看 STL 中相近容器：`std::vector`、`std::list`、`std::stack`、`std::queue`、`std::unordered_map`、`std::priority_queue`。

## 复杂度速查

| 数据结构 | 查找 | 插入 | 删除 | 备注 |
| --- | ---: | ---: | ---: | --- |
| 动态数组 | 按下标 `O(1)`，按值 `O(n)` | 尾部均摊 `O(1)`，中间 `O(n)` | 中间 `O(n)` | 连续内存，缓存友好 |
| 链表 | `O(n)` | 已知节点后 `O(1)` | 已知前驱 `O(1)` | 指针灵活，但随机访问慢 |
| 栈 | 只看栈顶 `O(1)` | `O(1)` | `O(1)` | 后进先出 |
| 队列 | 只看队首 `O(1)` | `O(1)` | `O(1)` | 先进先出 |
| 哈希表 | 平均 `O(1)` | 平均 `O(1)` | 平均 `O(1)` | 依赖哈希质量和负载因子 |
| BST | 平均 `O(log n)`，最坏 `O(n)` | 同左 | 同左 | 未平衡时可能退化 |
| 堆 | 查最高优先级 `O(1)` | `O(log n)` | `O(log n)` | 适合优先级队列 |
| 图邻接表 | 看算法 | 加边 `O(1)` | 通常需扫描 | 稀疏图常用 |

## 这个仓库刻意没有做什么

- 没有追求生产级 allocator、异常安全细节和迭代器完整规范。
- 没有直接使用 GoogleTest，避免初学者先卡在依赖管理上。
- 没有实现红黑树、AVL、B+ 树等高级结构。建议先把 BST 和堆学扎实。

这些都可以作为后续扩展。
