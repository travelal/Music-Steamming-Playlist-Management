#ifndef HISTORY_STACK_H
#define HISTORY_STACK_H

#include "Song.h"
#include <stack>
#include <vector>

// =====================================================================
// Class: HistoryStack
// Source: Topic brief (image) - "Stack: Quan ly lich su 'Recently
//         Played' (vua nghe xong) de quay lai." (Stack manages the
//         'Recently Played' history so the user can go back.)
//         Report 1 - 1.2.1 #6 Play History Management:
//         "LIFO stack mechanism using std::stack<Song*> ... push() on
//         playback initiation; top()/pop() yielding O(1) tracking."
//         Report 3 - 3.2 Conceptual Framework: Stack handles the
//         'Back' feature in parallel with the CDLL playlist.
//
// NOTE: this is intentionally a SEPARATE structure from the CDLL's
// prev pointer. CDLL Next/Previous move through playlist ORDER;
// the Stack instead remembers the ACTUAL sequence of songs that were
// played (which matters once Shuffle is enabled), so "Back" always
// returns to what the user truly heard last - not just the previous
// node in the list.
// =====================================================================
class HistoryStack {
private:
    std::stack<Song> historyStack;

public:
    void push(const Song& song);
    Song pop();              // throws std::runtime_error if empty
    Song peek() const;       // throws std::runtime_error if empty
    bool isEmpty() const;
    int size() const;

    // Prints the "Recently Played" list (most recent first) without
    // mutating the stack.
    void displayHistory() const;
};

#endif // HISTORY_STACK_H
