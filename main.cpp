#include <iostream>
#include <string>
#include "Playlist.h"
#include "Song.h"

using namespace std;

void showMenu() {
    cout << "\n================ MENU QUAN LY PLAYLIST ================\n";
    cout << "1. Them bai hat vao danh sach (addSong)\n";
    cout << "2. Hien thi toan bo danh sach (displayPlaylist)\n";
    cout << "3. Cap nhat thong tin bai hat (updateSong)\n";
    cout << "4. Xoa bai hat khoi danh sach (removeSong)\n";
    cout << "5. Tim kiem bai hat theo tu khoa (searchSong)\n";
    cout << "0. Thoat chuong trinh\n";
    cout << "=======================================================\n";
    cout << "Nhap lua chon cua ban: ";
}

int main() {
    Playlist myPlaylist; 
    int choice;
	myPlaylist.loadFromFile();
	
    do {
        showMenu();
        if (!(cin >> choice)) {
            cout << "Du lieu nhap vao khong hop le! Vui long nhap so.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore(); 

        switch (choice) {
            case 1: {
                string title, artist;
                int duration;
                cout << "\n--- THEM BAI HAT MOI ---\n";
                cout << "Nhap ten bai hat: ";
                getline(cin, title);
                cout << "Nhap ten ca si: ";
                getline(cin, artist);
                cout << "Nhap thoi luong (giay): ";
                cin >> duration;
                cin.ignore(); 

                Song s(title, artist, duration);
                myPlaylist.addSong(s);
                cout << "=> Da them bai hat thanh cong!\n";
                break;
            }
            case 2:
                cout << "\n--- DANH SACH BAI HAT CO TRONG PLAYLIST ---\n";
                cout << "\n STT - Title - Artist - Duration \n";
                myPlaylist.displayPlaylist();
                break;

            case 3: {
                cout << "\n--- CAP NHAT THONG TIN BAI HAT ---\n";
                if (myPlaylist.isEmpty()) {
                    cout << "Playlist dang trong, khong the cap nhat!\n";
                    break;
                }
                int pos;
                cout << "Nhap vi tri can cap nhat (1 -> " << myPlaylist.getSize() << "): ";
                cin >> pos;
                cin.ignore(); 
                myPlaylist.updateSong(pos);
                break;
            }
            case 4: {
                cout << "\n--- XOA BAI HAT ---\n";
                if (myPlaylist.isEmpty()) {
                    cout << "Playlist dang trong, khong the xoa!\n";
                    break;
                }
                int pos;
                cout << "Nhap vi tri can xoa (1 -> " << myPlaylist.getSize() << "): ";
                cin >> pos;
                cin.ignore();
                myPlaylist.removeSong(pos);
                break;
            }
            case 5: {
                cout << "\n--- TIM KIEM BAI HAT ---\n";
                string keyword;
                cout << "Nhap tu khoa tim kiem: ";
                getline(cin, keyword);
                myPlaylist.searchSong(keyword);
                break;
            }
            case 0:
            	myPlaylist.saveToFile();	
                cout << "Dang thoat chuong trinh. Tam biet!\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
                break;
        }
        if (choice != 0) {
            cout << "\nNhan Enter de tiep tuc...";
            cin.get();
        }
    } while (choice != 0);

    return 0;
}