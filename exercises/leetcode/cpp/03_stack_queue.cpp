#include "../leetcode_support.hpp"

#include <cassert>

namespace chapter03 {

bool isValid(const std::string& s) {
    std::stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if (st.empty()) {
                return false;
            }
            const char t = st.top();
            st.pop();
            if ((c == ')' && t != '(') ||
                (c == ']' && t != '[') ||
                (c == '}' && t != '{')) {
                return false;
            }
        }
    }
    return st.empty();
}

class MinStack {
public:
    void push(int val) {
        values_.push(val);
        if (mins_.empty() || val <= mins_.top()) {
            mins_.push(val);
        }
    }

    void pop() {
        if (values_.top() == mins_.top()) {
            mins_.pop();
        }
        values_.pop();
    }

    int top() const {
        return values_.top();
    }

    int getMin() const {
        return mins_.top();
    }

private:
    std::stack<int> values_;
    std::stack<int> mins_;
};

int evalRPN(const std::vector<std::string>& tokens) {
    std::stack<int> st;
    for (const auto& t : tokens) {
        if (t == "+" || t == "-" || t == "*" || t == "/") {
            const int b = st.top();
            st.pop();
            const int a = st.top();
            st.pop();
            if (t == "+") st.push(a + b);
            else if (t == "-") st.push(a - b);
            else if (t == "*") st.push(a * b);
            else st.push(a / b);
        } else {
            st.push(std::stoi(t));
        }
    }
    return st.top();
}

std::vector<int> dailyTemperatures(const std::vector<int>& temperatures) {
    const int n = static_cast<int>(temperatures.size());
    std::vector<int> ans(n, 0);
    std::stack<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
            const int j = st.top();
            st.pop();
            ans[j] = i - j;
        }
        st.push(i);
    }
    return ans;
}

int largestRectangleArea(std::vector<int> heights) {
    heights.push_back(0);
    std::stack<int> st;
    int ans = 0;
    for (int i = 0; i < static_cast<int>(heights.size()); ++i) {
        while (!st.empty() && heights[i] < heights[st.top()]) {
            const int h = heights[st.top()];
            st.pop();
            const int left = st.empty() ? -1 : st.top();
            ans = std::max(ans, h * (i - left - 1));
        }
        st.push(i);
    }
    return ans;
}

void run() {
    assert(isValid("()[]{}"));
    assert(!isValid("(]"));

    MinStack st;
    st.push(-2);
    st.push(0);
    st.push(-3);
    assert(st.getMin() == -3);
    st.pop();
    assert(st.top() == 0);
    assert(st.getMin() == -2);

    assert(evalRPN({"2", "1", "+", "3", "*"}) == 9);
    assert((dailyTemperatures({73,74,75,71,69,72,76,73}) == std::vector<int>{1,1,4,2,1,1,0,0}));
    assert(largestRectangleArea({2,1,5,6,2,3}) == 10);
}

} // namespace chapter03

int main() {
    chapter03::run();
    return 0;
}

