#ifndef FORWARD_STACK_H
#define FORWARD_STACK_H

#include "Song.h"
#include <stack>

// =====================================================================
// Class: ForwardStack
// Stack luu tru cac bai hat vua "di lui" (sau khi nhan Go Back).
//
// Flow:
//   Go Back    -> pop tu HistoryStack, push vao ForwardStack
//   Go Forward -> pop tu ForwardStack, push lai vao HistoryStack
//   Play / Next / Previous / playSong(pos) -> clear() de xoa forward
//
// Ket qua: ung xu giong trinh duyet web - Back/Forward hoat dong
// dung nhu mong doi, va forward history bi xoa khi co hanh dong moi.
// =====================================================================
class ForwardStack {
private:
    std::stack<Song> forwardStack;

public:
    void push(const Song& song);
    Song pop();           // throws std::runtime_error if empty
    Song peek() const;    // throws std::runtime_error if empty
    bool isEmpty() const;
    int size() const;
    void clear();         // xoa toan bo khi phat bai moi / Next / Previous

    // In noi dung stack (khong thay doi stack that)
    void displayForward() const;
};

#endif // FORWARD_STACK_H
