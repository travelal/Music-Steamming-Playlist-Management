#include "Playlist.h"
#include <iostream>
using namespace std;

void showMenu() {
    cout << "\n========== MENU ==========" << endl;
    cout << "1. Add Song To Playlist" << endl;
    cout << "2. Show playlist" << endl;
    cout << "3. Update Song" << endl;
    cout << "4. Remove Song from the Playlist" << endl;
    cout << "5. Search From Playlist" << endl;
    cout << "6. Play Song" << endl;
    cout << "7. The Next Song" << endl;
    cout << "8. The Previous Song" << endl;
    cout << "9. Save To File" << endl;
    cout << "10. Load From File" << endl;
    // FIX: them 2 chuc nang lich su
    cout << "11. View Play History" << endl;
    cout << "12. Go Back (Previous Played)" << endl;
    cout << "0. Quit" << endl;
    cout << "Lua chon: ";
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
                int duration;
                cout << "Name of Song: ";
                getline(cin, title);
                cout << "The Artist: ";
                getline(cin, artist);
                cout << "Duration (s): ";
                cin >> duration;
                playlist.addSong(Song(title, artist, duration));
                break;
            }
            case 2:
                playlist.displayPlaylist();
                break;
            case 3: {
                int pos;
                cout << "Location need update: (1 -> " << playlist.getSize() << "): ";
                cin >> pos;
                playlist.updateSong(pos);
                break;
            }
            case 4: {
                int pos;
                cout << "Location need remove: (1 -> " << playlist.getSize() << "): ";
                cin >> pos;
                playlist.removeSong(pos);
                break;
            }
            case 5: {
                string keyword;
                cout << "Search for keyword: ";
                getline(cin, keyword);
                playlist.searchSong(keyword);
                break;
            }
            case 6: {
                int pos;
                cout << "Song Want to Play (1 -> " << playlist.getSize() << "): ";
                cin >> pos;
                playlist.playSong(pos);
                break;
            }
            case 7:
                playlist.nextSong();
                break;
            case 8:
                playlist.previousSong();
                break;
            case 9:
                playlist.saveToFile();
                cout << "=> Save To File Successfully!" << endl;
                break;
            case 10:
                playlist.clear();
                playlist.loadFromFile();
                cout << "=> Load From File Successfully!" << endl;
                playlist.displayPlaylist();
                break;
            // FIX: them 2 case moi
            case 11:
                playlist.viewHistory();
                break;
            case 12:
                playlist.goBack();
                break;
            case 0:
                playlist.saveToFile();
                cout << "Bye! Have a good day, sir!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
