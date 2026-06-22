#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "Playlist.h"
#include "HistoryStack.h"
#include "Song.h"
#include <queue>
#include <string>

// =====================================================================
// Class: MusicPlayer
// Source: Report 2 - 2.1 UML Class Diagram
//         Attributes: playlist : Playlist
//         Key Methods: showMenu(), processChoice(), run(), exitProgram()
//         Relationship: Association with Playlist
//
// Extended here (per Report 1 decomposition + Report 3 framework) with:
//   - HistoryStack  -> the Stack-based "Recently Played"/Back feature
//   - std::queue<Song> -> Report 1, item #5 "Add to Queue" (lets a user
//     line up a song without disturbing the main playlist order)
// =====================================================================
class MusicPlayer {
private:
    Playlist playlist;
    HistoryStack history;
    std::queue<Song> upNextQueue;
    bool isPlaying;

    void showMenu() const;
    void processChoice(int choice);

    // Menu action handlers
    void handleAddSong();
    void handleDeleteSong();
    void handleSearchSong();
    void handleDisplayPlaylist();
    void handleSortPlaylist();
    void handleStartPlayback();
    void handleNextSong();
    void handlePreviousSong();
    void handleToggleShuffle();
    void handleSetLoopMode();
    void handleAddToQueue();
    void handlePlayFromQueue();
    void handleShowHistory();
    void handleSaveToFile();
    void handleLoadFromFile();
    void seedSampleData();

public:
    explicit MusicPlayer(const std::string& playlistName);

    void run();
    void exitProgram();
};

#endif // MUSIC_PLAYER_H
