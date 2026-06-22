#include "HistoryStack.h"
#include <iostream>
#include <stdexcept>

void HistoryStack::push(const Song& song) {
    historyStack.push(song);
}

Song HistoryStack::pop() {
    if (historyStack.empty()) {
        throw std::runtime_error("History is empty - nothing to go back to.");
    }
    Song top = historyStack.top();
    historyStack.pop();
    return top;
}

Song HistoryStack::peek() const {
    if (historyStack.empty()) {
        throw std::runtime_error("History is empty.");
    }
    return historyStack.top();
}

bool HistoryStack::isEmpty() const {
    return historyStack.empty();
}

int HistoryStack::size() const {
    return static_cast<int>(historyStack.size());
}

void HistoryStack::displayHistory() const {
    std::cout << "\n=== Recently Played (most recent first) ===\n";
    if (historyStack.empty()) {
        std::cout << "  (no playback history yet)\n";
        return;
    }

    // std::stack khong co iterator, copy ra de duyet tu tren xuong
    // ma khong thay doi stack that.
    std::stack<Song> copy = historyStack;
    int index = 1;
    while (!copy.empty()) {
        std::cout << "  " << index << ". ";
        copy.top().displayInfo();   // goi Song::displayInfo() da them o Song.cpp
        copy.pop();
        index++;
    }
}
