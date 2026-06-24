#include "ForwardStack.h"
#include <iostream>
#include <stdexcept>

void ForwardStack::push(const Song& song) {
    forwardStack.push(song);
}

Song ForwardStack::pop() {
    if (forwardStack.empty()) {
        throw std::runtime_error("Forward stack is empty - nothing to go forward to.");
    }
    Song top = forwardStack.top();
    forwardStack.pop();
    return top;
}

Song ForwardStack::peek() const {
    if (forwardStack.empty()) {
        throw std::runtime_error("Forward stack is empty.");
    }
    return forwardStack.top();
}

bool ForwardStack::isEmpty() const {
    return forwardStack.empty();
}

int ForwardStack::size() const {
    return static_cast<int>(forwardStack.size());
}

// Xoa toan bo forward stack - goi khi Play / Next / Previous / playSong(pos)
void ForwardStack::clear() {
    while (!forwardStack.empty()) {
        forwardStack.pop();
    }
}

// In noi dung forward stack (khong thay doi stack that)
void ForwardStack::displayForward() const {
    std::cout << "\n=== Forward Queue (songs restorable via Go Forward) ===\n";
    if (forwardStack.empty()) {
        std::cout << "  (no forward history)\n";
        return;
    }
    std::stack<Song> copy = forwardStack;
    int index = 1;
    while (!copy.empty()) {
        std::cout << "  " << index << ". ";
        copy.top().displayInfo();
        copy.pop();
        index++;
    }
}
