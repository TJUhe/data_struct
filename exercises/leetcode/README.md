# LeetCode 题库总览

这套题库按数据结构分组，目标是把“结构原理”和“做题套路”绑定起来。每个专题页都包含：

- 题目描述
- 关键点
- 配套示意图
- 解题思路
- C++ 参考答案
- 常见坑点

建议顺序：

1. 先做专题页中的前 2 题。
2. 跟着解析把代码默写一遍。
3. 再做后 2 到 3 题，尝试不看答案独立写。

## 题单结构

| 专题 | 题量 | 文件 |
| --- | ---: | --- |
| 数组 / 前缀和 / 双指针 | 5 | [01_arrays_prefix_two_pointers.md](01_arrays_prefix_two_pointers.md) |
| 链表 | 5 | [02_linked_list.md](02_linked_list.md) |
| 栈 / 队列 | 5 | [03_stack_queue.md](03_stack_queue.md) |
| 哈希表 | 5 | [04_hash_table.md](04_hash_table.md) |
| 树 / BST | 5 | [05_tree_bst.md](05_tree_bst.md) |
| 堆 / 优先队列 | 5 | [06_heap_priority_queue.md](06_heap_priority_queue.md) |
| 图 | 5 | [07_graph.md](07_graph.md) |
| 排序 / 设计 | 5 | [08_sorting_design.md](08_sorting_design.md) |

总题量：40 题。

## 使用建议

- 如果你刚学完某个章节，就优先做对应专题。
- 如果一道题卡住超过 30 分钟，先看“思路”，再自己重写代码。
- 最后再用“复杂度”和“坑点”做一次复盘。
- 每道题先看“题目描述”和“关键点”，再看代码。这样更像正式刷题，而不是只看答案。

## 可编译源码

每个专题都对应一个可运行的 C++ 章节文件，放在 [cpp](cpp) 目录下：

| 专题 | 可执行目标 | 源文件 |
| --- | --- | --- |
| 数组 / 前缀和 / 双指针 | `leetcode_01_arrays_prefix_two_pointers` | [cpp/01_arrays_prefix_two_pointers.cpp](cpp/01_arrays_prefix_two_pointers.cpp) |
| 链表 | `leetcode_02_linked_list` | [cpp/02_linked_list.cpp](cpp/02_linked_list.cpp) |
| 栈 / 队列 | `leetcode_03_stack_queue` | [cpp/03_stack_queue.cpp](cpp/03_stack_queue.cpp) |
| 哈希表 | `leetcode_04_hash_table` | [cpp/04_hash_table.cpp](cpp/04_hash_table.cpp) |
| 树 / BST | `leetcode_05_tree_bst` | [cpp/05_tree_bst.cpp](cpp/05_tree_bst.cpp) |
| 堆 / 优先队列 | `leetcode_06_heap_priority_queue` | [cpp/06_heap_priority_queue.cpp](cpp/06_heap_priority_queue.cpp) |
| 图 | `leetcode_07_graph` | [cpp/07_graph.cpp](cpp/07_graph.cpp) |
| 排序 / 设计 | `leetcode_08_sorting_design` | [cpp/08_sorting_design.cpp](cpp/08_sorting_design.cpp) |

这些目标已经接入 `ctest`，也能在 VS Code 里直接选目标调试。

如果你想看单个题目的实现，直接打开对应章节文件，然后在 `run()` 里的断言附近下断点即可。每个专题文件都把 5 题打包到一个可执行程序里，便于一起跑，也便于单题调试。
