# 练习题

参考答案见 [SOLUTIONS.md](SOLUTIONS.md)。建议先独立做一遍，再用答案校对思路；数据结构题的价值大多藏在“为什么这样改指针/移动元素”的过程里。

如果你想做更系统的在线题训练，去看 [LeetCode 题库总览](leetcode/README.md)。

## 基础练习

1. 给 `DynamicArray` 增加 `pop_back` 和 `front/back`。
2. 给 `SinglyLinkedList` 增加 `find_middle`，要求只遍历一次。
3. 使用 `Stack` 实现十进制转二进制。
4. 使用 `CircularQueue` 模拟客服排队系统。
5. 给 `HashTable` 增加 `keys()`，返回所有 key。

## 进阶练习

1. 给 BST 增加 `min`、`max` 和 `floor`。
2. 给 BST 增加层序遍历。
3. 把 `BinaryHeap` 改造成最小堆，或通过比较器同时支持最大堆和最小堆。
4. 给 `WeightedGraph` 增加无权最短路径，返回具体路径而不只是距离。
5. 给排序算法加计数器，统计比较次数和交换次数。

## 综合练习

1. 实现一个表达式求值器，支持 `+ - * /` 和括号。
2. 实现一个任务调度器：任务有优先级和创建时间，优先级高的先执行，优先级相同则早创建的先执行。
3. 实现一个简单拼写纠错器：用哈希表存词典，给出编辑距离为 1 的候选词。
4. 实现图的拓扑排序，并检测环。
5. 给 LRU Cache 增加命中率统计。

## 建议提交方式

每完成一个练习就提交一次：

```powershell
git add .
git commit -m "exercise: implement dynamic array pop_back"
```
