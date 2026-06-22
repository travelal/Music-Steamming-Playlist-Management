#ifndef HISTORY_STACK_H
#define HISTORY_STACK_H

#include "Song.h"
#include <stack>

// =====================================================================
// Class: HistoryStack
// Stack quan ly lich su "Recently Played" de quay lai.
// LILO stack: push() khi bat dau phat; top()/pop() khi "Go Back".
//
// NOTE: Day la cau truc RIENG BIET voi CDLL's prev pointer.
// CDLL Next/Previous di chuyen theo THU TU PLAYLIST;
// Stack nay nho TRINH TU THUC TE cac bai da phat (quan trong khi
// Shuffle bat), nen "Back" luon quay ve bai nguoi dung thuc su nghe
// lan cuoi - khong phai node lien ke trong danh sach.
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

    // In danh sach "Recently Played" (moi nhat truoc) khong lam thay doi stack.
    void displayHistory() const;
};

#endif // HISTORY_STACK_H
