#include "Playlist.h"
#include <iostream>
using namespace std;

void showMenu() {
    cout << "\n========== MENU ==========" << endl;
    cout << "1. Them bai hat" << endl;
    cout << "2. Hien thi playlist" << endl;
    cout << "3. Cap nhat bai hat" << endl;
    cout << "4. Xoa bai hat" << endl;
    cout << "5. Tim kiem bai hat" << endl;
    cout << "6. Phat bai hat" << endl;
    cout << "7. Bai hat tiep theo" << endl;
    cout << "8. Bai hat truoc do" << endl;
    cout << "9. Luu vao file" << endl;
    cout << "10. Tai tu file" << endl;
    cout << "0. Thoat" << endl;
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
                cout << "Ten bai hat: ";
                getline(cin, title);
                cout << "Ca si: ";
                getline(cin, artist);
                cout << "Thoi luong (giay): ";
                cin >> duration;
                playlist.addSong(Song(title, artist, duration));
                break;
            }
            case 2:
                playlist.displayPlaylist();
                break;
            case 3: {
                int pos;
                cout << "Vi tri can cap nhat: ";
                cin >> pos;
                playlist.updateSong(pos);
                break;
            }
            case 4: {
                int pos;
                cout << "Vi tri can xoa: ";
                cin >> pos;
                playlist.removeSong(pos);
                break;
            }
            case 5: {
                string keyword;
                cout << "Tu khoa tim kiem: ";
                getline(cin, keyword);
                playlist.searchSong(keyword);
                break;
            }
            case 6: {
                int pos;
                cout << "Vi tri bai hat can phat: ";
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
                cout << "=> Da luu vao file!" << endl;
                break;
            case 10:
                playlist.clear();
                playlist.loadFromFile();
                cout << "=> Da tai lai tu file!" << endl;
                break;
            case 0:
                playlist.saveToFile();
                cout << "Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
    } while (choice != 0);

    return 0;
}