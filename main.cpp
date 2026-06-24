#include "Playlist.h"
#include <iostream>
using namespace std;

void showMenu() {
    cout << "\n========== MENU ==========" << endl;
    cout << "1.  Add Song To Playlist"      << endl;
    cout << "2.  Show Playlist"             << endl;
    cout << "3.  Update Song"               << endl;
    cout << "4.  Remove Song from Playlist" << endl;
    cout << "5.  Search From Playlist"      << endl;
    cout << "6.  Play Song"                 << endl;
    cout << "7.  Next Song"                 << endl;
    cout << "8.  Previous Song"             << endl;
    cout << "9.  Save To File"              << endl;
    cout << "10. Load From File"            << endl;
    cout << "11. View Play History"         << endl;
    cout << "12. Go Back"                   << endl;
    cout << "13. Go Forward"                << endl;  // NEW
    cout << "0.  Quit"                      << endl;
    cout << "Choice: ";
}

int main() {
    Playlist playlist;
    playlist.loadFromFile();

    int choice;
    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string title, artist;
                int    duration;
                cout << "Name of Song: ";
                getline(cin, title);
                cout << "The Artist: ";
                getline(cin, artist);
                cout << "Duration (s): ";
                cin  >> duration;
                playlist.addSong(Song(title, artist, duration));
                break;
            }
            case 2:
                playlist.displayPlaylist();
                break;

            case 3: {
                int pos;
                cout << "Location to update (1 -> " << playlist.getSize() << "): ";
                cin  >> pos;
                playlist.updateSong(pos);
                break;
            }
            case 4: {
                int pos;
                cout << "Location to remove (1 -> " << playlist.getSize() << "): ";
                cin  >> pos;
                playlist.removeSong(pos);
                break;
            }
            case 5: {
                string keyword;
                cout << "Search keyword: ";
                getline(cin, keyword);
                playlist.searchSong(keyword);
                break;
            }
            case 6: {
                int pos;
                cout << "Song to play (1 -> " << playlist.getSize() << "): ";
                cin  >> pos;
                playlist.playSong(pos);   // clears ForwardStack
                break;
            }
            case 7:
                playlist.nextSong();       // clears ForwardStack
                break;

            case 8:
                playlist.previousSong();   // clears ForwardStack
                break;

            case 9:
                playlist.saveToFile();
                cout << "=> Saved to file successfully!" << endl;
                break;

            case 10:
                playlist.clear();
                playlist.loadFromFile();
                cout << "=> Loaded from file successfully!" << endl;
                playlist.displayPlaylist();
                break;

            case 11:
                playlist.viewHistory();
                break;

            case 12:
                playlist.goBack();        // moves current -> ForwardStack
                break;

            case 13:                      // NEW
                playlist.goForward();     // moves ForwardStack top -> HistoryStack
                break;

            case 0:
                playlist.saveToFile();
                cout << "Bye! Have a good day!" << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
