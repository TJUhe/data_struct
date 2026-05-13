#include "ds/binary_heap.hpp"

#include <iostream>
#include <string>

struct Ticket {
    int priority;
    std::string title;
};

struct TicketPriority {
    bool operator()(const Ticket& lhs, const Ticket& rhs) const {
        return lhs.priority < rhs.priority;
    }
};

int main() {
    ds::BinaryHeap<Ticket, TicketPriority> queue;
    queue.push({2, "write README"});
    queue.push({5, "fix crash"});
    queue.push({1, "rename variable"});
    queue.push({4, "add tests"});

    while (!queue.empty()) {
        Ticket ticket = queue.pop();
        std::cout << "priority " << ticket.priority << ": " << ticket.title << '\n';
    }
    return 0;
}

