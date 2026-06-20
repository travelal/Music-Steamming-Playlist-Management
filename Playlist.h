#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Song.h"
#include <string>
using namespace std;

class Playlist {
private:
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

    void playSong(int position);
    void nextSong();
    void previousSong();
};

#endif