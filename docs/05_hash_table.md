# 05. 哈希表

哈希表试图把 key 直接映射到数组下标：

```text
bucket_index = hash(key) % bucket_count
```

理想情况下，查找、插入、删除都是平均 `O(1)`。

## 冲突

不同 key 可能映射到同一个桶，这叫冲突。常见处理方式：

- 拉链法：每个桶里放一个链表或小数组。
- 开放寻址：冲突后继续探测下一个位置。

本仓库使用拉链法：`std::vector<std::list<pair<Key, Value>>>`。

## 负载因子

负载因子：

```text
load_factor = 元素数量 / 桶数量
```

负载因子太高，冲突变多，链表变长，查找会退化。示例实现超过 0.75 时会扩容并重新哈希。

## 代码观察点

看 [include/ds/hash_table.hpp](../include/ds/hash_table.hpp)：

- `bucket_for`：根据 key 找桶。
- `insert_or_assign`：已有 key 就更新，不存在就插入。
- `rehash`：创建更多桶，把所有元素重新分布。

## 本章实验

运行：

```powershell
.\build\debug\bin\05_hash_table.exe
```

练习：

- 初始桶数量改成 2，插入更多单词，观察扩容。
- 写一个糟糕的哈希函数，让所有 key 都进同一个桶，体验退化。

