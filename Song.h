#ifndef SONG_H
#define SONG_H

#include <string>
using namespace std;

class Song {
private:
    string title;
    string artist;
    int duration; // tinh theo so giay

public:
    Song();
    Song(const string& t, const string& a, int d);

    string getTitle() const;
    string getArtist() const;
    int getDuration() const;

    void setTitle(const string& t);
    void setArtist(const string& a);
    void setDuration(int d);

    // Dung boi HistoryStack::displayHistory() de in thong tin bai hat
    void displayInfo() const;
};

#endif
