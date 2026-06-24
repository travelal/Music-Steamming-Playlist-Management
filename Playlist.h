#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Song.h"
#include "HistoryStack.h"
#include "ForwardStack.h"   // NEW: needed for go-forward navigation
#include <string>
using namespace std;

class Playlist {
private:
    // ---------------------------------------------------------------
    // CDLL node — unchanged from original
    // ---------------------------------------------------------------
    struct Node {
        Song data;
        Node* next;
        Node* prev;
        Node(const Song& s) : data(s), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    Node* currentTrack;
    int size;

    // ---------------------------------------------------------------
    // History system
    //   history : LIFO stack of every song played (most recent = top)
    //   forward : LIFO stack of songs moved aside by Go Back;
    //             cleared whenever a "new direction" action happens
    // ---------------------------------------------------------------
    HistoryStack history;
    ForwardStack forward;   // NEW

public:
    Playlist();
    ~Playlist();

    bool isEmpty() const;
    int getSize() const;
    void clear();

    void addSong(const Song& song);
    void displayPlaylist() const;
    void updateSong(int position);
    void removeSong(int position);
    void searchSong(const string& keyword);

    void loadFromFile();
    void saveToFile() const;

    void playSong(int position);    // clears ForwardStack
    void nextSong();                // clears ForwardStack
    void previousSong();            // clears ForwardStack

    void viewHistory() const;
    void goBack();      // moves current from HistoryStack -> ForwardStack
    void goForward();   // NEW: moves top of ForwardStack -> HistoryStack
};

#endif // PLAYLIST_H
