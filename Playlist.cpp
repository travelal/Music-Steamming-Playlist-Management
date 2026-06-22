#include "Playlist.h"
#include <iostream>
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

void Playlist::displayPlaylist() const{
    if (head == nullptr){
        cout<<"PlayList is empty!"<<endl;
        return;
    }
    Node* current = head;
    int index = 1;

    do{
        cout<< index << "." << current->data.getTitle() << " - " << current->data.getArtist() << " - " << current->data.getDuration() <<"s"<< endl;
        current = current->next;
        index++;
    } while (current != head);
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
    saveToFile();
    cout << "=> Remove song success! " << endl;
}

void Playlist::searchSong(const string& keyword){
    if (head == nullptr){
        cout << "Playlist is empty!" << endl;
        return;
    }

    Node* current = head;
    bool found = false;
    cout << "The keyword is : " << keyword << endl;
    do{
        if(current->data.getArtist().find(keyword)!= string::npos || current->data.getTitle().find(keyword)!= string::npos){
            cout << current->data.getTitle() << " - " << current->data.getArtist() << " - " << current->data.getDuration() << endl;
            found = true;
        }
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

    currentTrack = current;

    // FIX: luu bai vua phat vao lich su
    history.push(current->data);

    cout << "=> Now playing: " << current->data.getTitle()
         << " - " << current->data.getArtist()
         << " (" << current->data.getDuration() << "s)" << endl;
}

void Playlist::nextSong() {
    if (head == nullptr) {
        cout << "Playlist is empty!" << endl;
        return;
    }
    if (currentTrack == nullptr) {
        currentTrack = head;
    } else {
        currentTrack = currentTrack->next;
    }

    // FIX: luu bai vua chuyen sang vao lich su
    history.push(currentTrack->data);

    cout << "=> Now playing: " << currentTrack->data.getTitle()
         << " - " << currentTrack->data.getArtist()
         << " (" << currentTrack->data.getDuration() << "s)" << endl;
}

void Playlist::previousSong() {
    if (head == nullptr) {
        cout << "Playlist is empty!" << endl;
        return;
    }
    if (currentTrack == nullptr) {
        currentTrack = tail;
    } else {
        currentTrack = currentTrack->prev;
    }

    // FIX: luu bai vua chuyen sang vao lich su
    history.push(currentTrack->data);

    cout << "=> Now playing: " << currentTrack->data.getTitle()
         << " - " << currentTrack->data.getArtist()
         << " (" << currentTrack->data.getDuration() << "s)" << endl;
}

// FIX: them 2 method moi cho tinh nang lich su
void Playlist::viewHistory() const {
    history.displayHistory();
}

void Playlist::goBack() {
    if (history.isEmpty()) {
        cout << "No history - nothing to go back to." << endl;
        return;
    }
    if (history.size() == 1) {
        history.pop();
        currentTrack = nullptr;
        cout << "No previous song in history." << endl;
        return;
    }

    // Pop bai hien tai, peek bai truoc do
    history.pop();
    Song prev = history.peek();

    cout << "=> Going back to: " << prev.getTitle()
         << " - " << prev.getArtist()
         << " (" << prev.getDuration() << "s)" << endl;

    // Dong bo currentTrack voi CDLL
    if (head == nullptr) return;
    Node* cur = head;
    do {
        if (cur->data.getTitle() == prev.getTitle() &&
            cur->data.getArtist() == prev.getArtist()) {
            currentTrack = cur;
            break;
        }
        cur = cur->next;
    } while (cur != head);
}
