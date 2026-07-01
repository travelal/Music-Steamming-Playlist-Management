#include "Playlist.h"
#include <iostream>
using namespace std;

void showMenu() {
    cout << "\n========== MENU ==========" << endl;
    cout << "1. Add Song" << endl;
    cout << "2. Show the Playlist" << endl;
    cout << "3. Update Song" << endl;
    cout << "4. Remove Song" << endl;
    cout << "5. Search Song for Playlist" << endl;
    cout << "6. Play Song" << endl;
    cout << "7. Next Song" << endl;
    cout << "8. Previous Song" << endl;
    cout << "9. Save To File" << endl;
    cout << "10. Load To File" << endl;
    cout << "11. Show Recently Played" << endl;
    cout << "12. Back to Last Played" << endl;
    cout << "0. Exit" << endl;
    cout << "Your Choice: ";
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
                cout << "The title Song: ";
                getline(cin, title);
                cout << "The Artist : ";
                getline(cin, artist);
                cout << "Duration (s): ";
                cin >> duration;
                
                // Bắt buộc phải có dòng này để xóa ký tự xuống dòng (\n) sót lại sau khi nhập số duration
                cin.ignore(); 
        
                Song newSong(title, artist, duration);
                
                // Vòng lặp: Nếu bài hát bị trùng (addSong trả về false), bắt nhập lại title
                while (!playlist.addSong(newSong)) {
                    cout << "Please enter a different title: ";
                    getline(cin, title);
                    newSong.setTitle(title); // Cập nhật lại title mới cho bài hát
                }
                
                cout << "=> Add Song successfully." << endl;
                playlist.saveToFile();
                break;
            }
            case 2:{
                playlist.displayPlaylist();
                break;
			}
            case 3: {
                int pos;
                cout << "Location need update(1 - " << playlist.getSize() << ") :";
                cin >> pos;
                playlist.updateSong(pos);
                playlist.saveToFile();
                break;
            }
            case 4: {
                int pos;
                cout << "Location need remove(1 - " << playlist.getSize() << ") :";
                cin >> pos;
                playlist.removeSong(pos);
                playlist.saveToFile();
                break;
            }
            case 5: {
                string keyword;
                cout << "Keyword to Search: ";
                getline(cin, keyword);
                playlist.searchSong(keyword);
                break;
            }
            case 6: {
                int pos;
                playlist.displayPlaylist();
                cout << "Choose Song you want to play (1 - " << playlist.getSize() << ") :";
                cin >> pos;
                playlist.playSong(pos);
                break;
            }
            case 7:{
                playlist.nextSong();
                break;
			}
            case 8:{
                playlist.previousSong();
                break;
            }
            case 9:{
                playlist.saveToFile();
                cout << "=> Save to file successfully!" << endl;
                break;
            }
            case 10: {
    			playlist.clear();  // Xóa playlist cũ
    			playlist.loadFromFile();  // Load playlist mới (đã sửa để giữ lịch sử)
    			cout << "\n Load file successfully! (" << playlist.getSize() << " songs loaded)" << endl;
    			if (playlist.getSize() > 0) {
        			cout << " History preserved!" << endl;
        			playlist.displayPlaylist();
    			} else {
        			cout << " Playlist file is empty or not found!" << endl;
    			}
    			break;
			}
            case 11:{
            	playlist.displayRecentlyPlayed();
            	break;
            }
            case 12:{
            	playlist.backtoLastPlayed();
            	break;
            }
            case 0:{
                playlist.saveToFile();
                cout << "Sir, have a nice day and chill your days !" << endl;
                break;
            }
            default:
                cout << "Invalid Choice" << endl;
        }
    } while (choice != 0);

    return 0;
}