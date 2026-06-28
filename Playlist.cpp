#include "Playlist.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <string>
#include <fstream>
using namespace std;

Playlist::Playlist(){
	head = nullptr;
	tail = nullptr;
	size = 0;
	currentTrack = nullptr;
}

Playlist::~Playlist(){
	clear();
}

bool Playlist::isEmpty() const{
	return size == 0;
}

int Playlist::getSize() const{
	return size;
}

void Playlist::clear(){
	if (head == nullptr) return;
	Node* current = head;
	Node* nextNode = nullptr;
	do{
		nextNode = current->next;
		delete current;
		current = nextNode;
	} while (current != head);
	head = nullptr;
	tail = nullptr;
	size = 0;
	currentTrack = nullptr;
}

void Playlist::addSong(const Song&song){
	Node* newNode = new Node(song);
	if (head == nullptr){
		head = newNode;
		tail = newNode;
		newNode->next = newNode;
		newNode->prev = newNode;
	}
	else{
		tail->next= newNode;
		newNode->next = head;
		newNode->prev = tail;
		head->prev = newNode;
		tail = newNode;
	}
	size++;
}

void Playlist::displayPlaylist() const {
    if (head == nullptr) {
        cout << "Playlist is empty!" << endl;
        return;
    }

    cout << "\n========================================================================\n";
    cout << left << setw(6)  << "#" 
         << setw(30) << "Title" 
         << setw(25) << "Artist" 
         << setw(12) << "Duration" << endl;
    cout << "------------------------------------------------------------------------\n";

    Node* current = head;
    int index = 1;
    
    do {
        string durationStr = to_string(current->data.getDuration()) + "s";
        cout << left << setw(6)  << index 
             << setw(30) << current->data.getTitle() 
             << setw(25) << current->data.getArtist() 
             << setw(12) << durationStr << endl;
             
        current = current->next;
        index++;
    } while (current != head);

    cout << "========================================================================\n\n";
}
void Playlist::updateSong(int position){
	if (head == nullptr){
	cout<<"PlayList is empty!"<<endl;
	return;
	}
	
	if(position < 1 || position > size){
		cout << "Invalid position!" << endl;
        return;
	}
	
	Node* current = head;
	for(int i = 1; i < position; i++){
		current = current->next;
	}
	int choice;
	cout << "-------------Update Song-------------" << endl;
	cout << "1. Update Title" << endl;
    cout << "2. Update Artist" << endl;
    cout << "3. Update Duration" << endl;
    cout << "Choose: ";
    cin >> choice;
    cin.ignore();
    
    switch (choice){
    	 case 1:
        {
            string newTitle;
            cout << "Enter new title: ";
            getline(cin, newTitle);
            current->data.setTitle(newTitle);
            break;
        }

        case 2:
        {
            string newArtist;
            cout << "Enter new artist: ";
            getline(cin, newArtist);
            current->data.setArtist(newArtist);
            break;
        }

        case 3:
        {
            int newDuration;
            cout << "Enter new duration (seconds): ";
            cin >> newDuration;
            current->data.setDuration(newDuration);
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
            return;
	}
	cout << "=> Update done" << endl;
}

void Playlist::removeSong(int position){
    if (head == nullptr) {
        cout << "Playlist is empty!" << endl;
        return;
    }

    if (position < 1 || position > size) {
        cout << "Invalid position!" << endl;
        return;
    }

    Node* temp = nullptr;
    
    if (position == 1) {
        temp = head;
        if (size == 1) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            head->prev = tail;
            tail->next = head;
        }
        if (currentTrack == temp) currentTrack = nullptr;
        delete temp;
    } 

    else {
        Node* current = head;
        for (int i = 1; i < position - 1; i++) {
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;
        temp->next->prev = current;
        if (temp == tail) {
            tail = current;
        }
        if (currentTrack == temp) currentTrack = nullptr;
        delete temp;
    }
    size--;
    cout << "=> Remove song success! " << endl;
}

string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return tolower(c);
    });
    return str;
}

void Playlist::searchSong(const string& keyword){
    if (head == nullptr){
        cout << "Playlist is empty!" << endl;
        return;
    }
    
    string lowerKeyword = toLowerCase(keyword);
    
    Node* current = head;
    bool found = false;
    int index = 1;
    cout << "The keyword is : " << keyword << endl;
    
    do {
        string lowerArtist = toLowerCase(current->data.getArtist());
        string lowerTitle = toLowerCase(current->data.getTitle());
        
        if(lowerArtist.find(lowerKeyword) != string::npos || lowerTitle.find(lowerKeyword) != string::npos){
            cout << current->data.getTitle() << " - " << current->data.getArtist() << " - " << current->data.getDuration() << endl;
            found = true;
        }
        
        index++;
        current = current->next;
    } while(current != head);
    
    if(!found){
        cout << "No songs were found that match the keywords you entered!" << endl;
    }
}

void Playlist::loadFromFile() {
    ifstream inFile("playlist.txt");
    if (!inFile) return;

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        if (pos1 != string::npos && pos2 != string::npos) {
            string title = line.substr(0, pos1);
            string artist = line.substr(pos1 + 1, pos2 - pos1 - 1);
            int duration = stoi(line.substr(pos2 + 1));

            addSong(Song(title, artist, duration));
        }
    }
    inFile.close();
}

void Playlist::saveToFile() const {
    ofstream outFile("playlist.txt");
    if (!outFile) return;

    if (head == nullptr) {
        outFile.close();
        return;
    }

    Node* current = head;
    do {
        outFile << current->data.getTitle() << "|"
                << current->data.getArtist() << "|"
                << current->data.getDuration() << endl;
        current = current->next;
    } while (current != head);
    outFile.close();
}

void Playlist::playSong(int position) {
    if (head == nullptr) {
        cout << "Playlist is empty!" << endl;
        return;
    }
    if (position < 1 || position > size) {
        cout << "Invalid position!" << endl;
        return;
    }

    Node* current = head;
    for (int i = 1; i < position; i++) {
        current = current->next;
    }
    
    while (!forwardStack.empty()) forwardStack.pop();
    
    if(currentTrack != nullptr){
    	historyStack.push(currentTrack->data);
	}
	
    currentTrack = current;
    cout << "=> Now playing: " << current->data.getTitle()
         << " - " << current->data.getArtist()
         << " (" << current->data.getDuration() << "s)" << endl;
}

void Playlist::nextSong() {
    if (head == nullptr) {
        cout << "Playlist is empty!" << endl;
        return;
    }
    
	while (!forwardStack.empty()) forwardStack.pop();
      
    if (currentTrack == nullptr) {
        currentTrack = head;
    } else {
    	historyStack.push(currentTrack->data);
        currentTrack = currentTrack->next;
    }
    cout << "=> Now playing: " << currentTrack->data.getTitle()
         << " - " << currentTrack->data.getArtist()
         << " (" << currentTrack->data.getDuration() << "s)" << endl;
}

void Playlist::previousSong() {
    if (head == nullptr) {
        cout << "Playlist is empty!" << endl;
        return;
    }

    while (!forwardStack.empty()) forwardStack.pop();
      
    if (currentTrack == nullptr) {
        currentTrack = tail;
    } else {
    	historyStack.push(currentTrack->data);
        currentTrack = currentTrack->prev;
    }
    cout << "=> Now playing: " << currentTrack->data.getTitle()
         << " - " << currentTrack->data.getArtist()
         << " (" << currentTrack->data.getDuration() << "s)" << endl;
}

void Playlist::displayRecentlyPlayed() const{
	stack<Song> fullTimeline = historyStack;
	
	if (currentTrack != nullptr) {
        fullTimeline.push(currentTrack->data); //hiện tại
    }
    
    stack<Song> tempForward = forwardStack; 
    while (!tempForward.empty()) {             //Nạp Tương lai lên trên cùng
        fullTimeline.push(tempForward.top());
        tempForward.pop();
    }
    
    if (fullTimeline.empty()) {
        cout << "=> History is empty!" << endl;
        return;
    }

    cout << "\n================ RECENTLY PLAYED ================\n";
    cout << left << setw(6)  << "#" 
         << setw(30) << "Title" 
         << setw(25) << "Artist" << endl;
    cout << "-------------------------------------------------\n";

    int index = 1;
    // Bắt đầu in từ trên cùng của fullTimeline (bài hát mới nhất)
    while (!fullTimeline.empty() && index <= 15) {
        Song s = fullTimeline.top();
        
        // Thêm dấu sao (*) cho bài hát đang phát hiện tại
        string indicator = (currentTrack != nullptr && 
                            s.getTitle() == currentTrack->data.getTitle() && 
                            s.getArtist() == currentTrack->data.getArtist()) ? " (*)" : "";
                            
        cout << left << setw(6)  << index 
             << setw(30) << (s.getTitle() + indicator) 
             << setw(25) << s.getArtist() << endl;
        
        fullTimeline.pop();
        index++;
    }
    cout << "  (*) : Currently playing\n";
    cout << "=================================================\n\n";
}

void Playlist::backtoLastPlayed() {
    if (historyStack.empty()) {
        cout << "=> No previous song in history to go back to!" << endl;
        return;
    }
    
    if (currentTrack != nullptr) {
        forwardStack.push(currentTrack->data);
    }
    
    Song lastPlayed = historyStack.top();
    historyStack.pop();

    if (head == nullptr) return;
    
    Node* current = head;
    bool found = false;
    do {
        if (current->data.getTitle() == lastPlayed.getTitle() && 
            current->data.getArtist() == lastPlayed.getArtist()) {
            
 
            currentTrack = current;
            found = true;
            break;
        }
        current = current->next;
    } while (current != head);

    if (found) {
        cout << "=> (Back) Now playing: " << currentTrack->data.getTitle()
             << " - " << currentTrack->data.getArtist()
             << " (" << currentTrack->data.getDuration() << "s)" << endl;
    } else {
        cout << "=> Cannot play! The song '" << lastPlayed.getTitle() 
             << "' was removed from the playlist." << endl;
    }
}