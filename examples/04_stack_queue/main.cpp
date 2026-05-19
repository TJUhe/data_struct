#include "ds/queue.hpp"
#include "ds/stack.hpp"

#include <iostream>
#include <string>

bool is_balanced(const std::string& text) {
   ds::Stack<char> stack;
    for (char ch : text) {
        if (ch == '(' || ch == '[' || ch == '{') {
            stack.push(ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (stack.empty()) {
                return false;
            }
            const char open = stack.pop();
            if ((open == '(' && ch != ')') ||
                (open == '[' && ch != ']') ||
                (open == '{' && ch != '}')) {
                return false;
            }
        }
    }
    return stack.empty();
}

std::string to_binary(size_t value){
    if (value == 0)
    {
        return "0";
    }

    ds::Stack<char> bits;
    while(value > 0){
        bits.push(static_cast<char>('0' + value%2));
        value /= 2;
    }

    std::string res;
    while (!bits.empty())
    {
        res.push_back(bits.pop());
    }
    return res;
}

int main() {
    std::cout << "Stack example: bracket matching\n";
    for (const std::string text : {"{[()]}", "{[(])}", "(()[])"}) {
        std::cout << text << " -> " << (is_balanced(text) ? "balanced" : "not balanced") << '\n';
    }

    std::cout << "\nQueue example: print jobs\n";
    ds::CircularQueue<std::string> queue(3);
    queue.push("chapter-01.pdf");
    queue.push("chapter-02.pdf");
    queue.push("homework.cpp");
    queue.push("graph-notes.md");

    while (!queue.empty()) {
        std::cout << "printing " << queue.pop() << '\n';
    }
    return 0;
}

