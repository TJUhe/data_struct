# 栈 / 队列

栈和队列题，核心是“限制访问方式”：

- 栈：只看顶部。
- 队列：先进先出。

这类题很适合训练“什么时候该存状态，什么时候该弹出状态”。

![栈与队列示意图](../../docs/images/04_stack_queue.svg)

## 20. Valid Parentheses

题目描述：给定一个只包含括号字符的字符串，判断它是否有效。有效字符串要求左括号和右括号正确配对，且顺序正确。

示意：`({[]})` 合法，`(]` 不合法。

关键点：遇到左括号时记住它，遇到右括号时必须匹配最近出现的左括号，所以要用栈。

思路：遇到左括号入栈，遇到右括号就检查栈顶是否匹配。

复杂度：时间 `O(n)`，空间 `O(n)`。

```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') st.push(c);
            else {
                if (st.empty()) return false;
                char t = st.top(); st.pop();
                if ((c == ')' && t != '(') ||
                    (c == ']' && t != '[') ||
                    (c == '}' && t != '{')) return false;
            }
        }
        return st.empty();
    }
};
```

## 155. Min Stack

题目描述：设计一个支持 `push`、`pop`、`top` 和 `getMin` 的栈，其中 `getMin` 必须是 `O(1)`。

示意：主栈放值，辅助栈同步记“当前最小值”。

关键点：不能每次都扫描一遍栈找最小值，应该在入栈时同步维护一个“最小值历史”。

思路：辅助栈记录“到当前为止的最小值”。主栈压入数据，辅栈同步维护最小值。

复杂度：全部操作都是 `O(1)`。

```cpp
class MinStack {
    stack<int> st, mn;
public:
    void push(int val) {
        st.push(val);
        if (mn.empty() || val <= mn.top()) mn.push(val);
    }
    void pop() {
        if (st.top() == mn.top()) mn.pop();
        st.pop();
    }
    int top() { return st.top(); }
    int getMin() { return mn.top(); }
};
```

## 150. Evaluate Reverse Polish Notation

题目描述：给定一个逆波兰表达式数组，计算它的结果。

示意：`["2","1","+","3","*"] -> 9`

关键点：后缀表达式的运算顺序已经写在序列里了，所以看到数字就入栈，看到运算符就弹出两个数计算。

思路：数字入栈，遇到运算符就弹出两个数计算，再把结果压回去。

复杂度：时间 `O(n)`，空间 `O(n)`。

```cpp
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for (auto& t : tokens) {
            if (t == "+" || t == "-" || t == "*" || t == "/") {
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                if (t == "+") st.push(a + b);
                else if (t == "-") st.push(a - b);
                else if (t == "*") st.push(a * b);
                else st.push(a / b);
            } else st.push(stoi(t));
        }
        return st.top();
    }
};
```

## 739. Daily Temperatures

题目描述：给定每天的气温，返回每一天需要等待多少天才能等到一个更高的温度。

示意：`73 74 75 71 69 72 76 73 -> 1 1 4 2 1 1 0 0`

关键点：要找“下一个更大元素”，这类题一般都能用单调栈。

思路：单调栈存下标，栈内温度保持递减。当前温度更高时，持续弹栈并计算距离。

复杂度：时间 `O(n)`，空间 `O(n)`。

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n);
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int j = st.top(); st.pop();
                ans[j] = i - j;
            }
            st.push(i);
        }
        return ans;
    }
};
```

## 84. Largest Rectangle in Histogram

题目描述：给定一组柱子的高度，求能组成的最大矩形面积。

示意：`[2,1,5,6,2,3] -> 10`

关键点：某个柱子作为最矮高度时，它能扩展到哪里，取决于左右第一个更矮的柱子。

思路：单调递增栈。遇到更矮的柱子时，说明栈顶柱子作为最矮高度的范围已经确定，可以计算面积。

复杂度：时间 `O(n)`，空间 `O(n)`。

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        stack<int> st;
        int ans = 0;
        for (int i = 0; i < (int)heights.size(); ++i) {
            while (!st.empty() && heights[i] < heights[st.top()]) {
                int h = heights[st.top()]; st.pop();
                int left = st.empty() ? -1 : st.top();
                ans = max(ans, h * (i - left - 1));
            }
            st.push(i);
        }
        return ans;
    }
};
```
