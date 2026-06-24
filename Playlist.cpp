#include "Playlist.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// ===================================================================
// Constructor / Destructor
// ===================================================================
Playlist::Playlist(){
    head         = nullptr;
    tail         = nullptr;
    size         = 0;
    currentTrack = nullptr;
}

Playlist::~Playlist(){
    clear();
}

// ===================================================================
// Utility
// ===================================================================
bool Playlist::isEmpty() const{
    return size == 0;
}

int Playlist::getSize() const{
    return size;
}

void Playlist::clear(){
    if (head == nullptr) return;
    Node* current  = head;
    Node* nextNode = nullptr;
    do{
        nextNode = current->next;
        delete current;
        current  = nextNode;
    } while (current != head);
    head         = nullptr;
    tail         = nullptr;
    size         = 0;
    currentTrack = nullptr;
}

// ===================================================================
// CDLL operations — all unchanged from original
// ===================================================================
void Playlist::addSong(const Song& song){
    Node* newNode = new Node(song);
    if (head == nullptr){
        head          = newNode;
        tail          = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    }
    else{
        tail->next    = newNode;
        newNode->next = head;
        newNode->prev = tail;
        head->prev    = newNode;
        tail          = newNode;
    }
    size++;
}

void Playlist::displayPlaylist() const{
    if (head == nullptr){
        cout << "PlayList is empty!" << endl;
        return;
    }
    Node* current = head;
    int   index   = 1;
    do{
        cout << index << "." << current->data.getTitle()
             << " - "       << current->data.getArtist()
             << " - "       << current->data.getDuration() << "s" << endl;
        current = current->next;
        index++;
    } while (current != head);
}

void Playlist::updateSong(int position){
    if (head == nullptr){
        cout << "PlayList is empty!" << endl;
        return;
    }
    if (position < 1 || position > size){
        cout << "Invalid position!" << endl;
        return;
    }

    Node* current = head;
    for (int i = 1; i < position; i++){
        current = current->next;
    }

    int choice;
    cout << "-------------Update Song-------------" << endl;
    cout << "1. Update Title"    << endl;
    cout << "2. Update Artist"   << endl;
    cout << "3. Update Duration" << endl;
    cout << "Choose: ";
    cin  >> choice;
    cin.ignore();

    switch (choice){
        case 1:{
            string newTitle;
            cout << "Enter new title: ";
            getline(cin, newTitle);
            current->data.setTitle(newTitle);
            break;
        }
        case 2:{
            string newArtist;
            cout << "Enter new artist: ";
            getline(cin, newArtist);
            current->data.setArtist(newArtist);
            break;
        }
        case 3:{
            int newDuration;
            cout << "Enter new duration (seconds): ";
            cin  >> newDuration;
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
    if (head == nullptr){
        cout << "Playlist is empty!" << endl;
        return;
    }
    if (position < 1 || position > size){
        cout << "Invalid position!" << endl;
        return;
    }

    Node* temp = nullptr;

    if (position == 1){
        temp = head;
        if (size == 1){
            head = nullptr;
            tail = nullptr;
        } else {
            head       = head->next;
            head->prev = tail;
            tail->next = head;
        }
        if (currentTrack == temp) currentTrack = nullptr;
        delete temp;
    }
    else{
        Node* current = head;
        for (int i = 1; i < position - 1; i++){
            current = current->next;
        }
        temp                = current->next;
        current->next       = temp->next;
        temp->next->prev    = current;
        if (temp == tail)   tail = current;
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
    bool  found   = false;
    cout << "The keyword is : " << keyword << endl;
    do{
        if (current->data.getArtist().find(keyword) != string::npos ||
            current->data.getTitle().find(keyword)  != string::npos){
            cout << current->data.getTitle()
                 << " - " << current->data.getArtist()
                 << " - " << current->data.getDuration() << endl;
            found = true;
        }
        current = current->next;
    } while (current != head);

    if (!found){
        cout << "No songs were found that match the keywords you entered!" << endl;
    }
}

// ===================================================================
// File I/O — unchanged from original
// ===================================================================
void Playlist::loadFromFile(){
    ifstream inFile("playlist.txt");
    if (!inFile) return;

    string line;
    while (getline(inFile, line)){
        if (line.empty()) continue;

        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        if (pos1 != string::npos && pos2 != string::npos){
            string title  = line.substr(0, pos1);
            string artist = line.substr(pos1 + 1, pos2 - pos1 - 1);
            int duration  = stoi(line.substr(pos2 + 1));
            addSong(Song(title, artist, duration));
        }
    }
    inFile.close();
}

void Playlist::saveToFile() const{
    ofstream outFile("playlist.txt");
    if (!outFile) return;

    if (head == nullptr){
        outFile.close();
        return;
    }

    Node* current = head;
    do{
        outFile << current->data.getTitle()   << "|"
                << current->data.getArtist()  << "|"
                << current->data.getDuration() << endl;
        current = current->next;
    } while (current != head);
    outFile.close();
}

// ===================================================================
// Playback — CHANGED: each method clears ForwardStack so that
// a new "direction" always invalidates the go-forward history.
// ===================================================================

// Play a specific song by position (manual selection)
void Playlist::playSong(int position){
    if (head == nullptr){
        cout << "Playlist is empty!" << endl;
        return;
    }
    if (position < 1 || position > size){
        cout << "Invalid position!" << endl;
        return;
    }

    Node* current = head;
    for (int i = 1; i < position; i++){
        current = current->next;
    }

    currentTrack = current;

    // NEW: selecting a specific song is a new "branch" — clear forward history
    forward.clear();

    history.push(current->data);

    cout << "=> Now playing: " << current->data.getTitle()
         << " - "              << current->data.getArtist()
         << " ("               << current->data.getDuration() << "s)" << endl;
}

// Advance to the next song in the CDLL
void Playlist::nextSong(){
    if (head == nullptr){
        cout << "Playlist is empty!" << endl;
        return;
    }

    if (currentTrack == nullptr){
        currentTrack = head;
    } else {
        currentTrack = currentTrack->next;
    }

    // NEW: moving forward in playlist invalidates go-forward history
    forward.clear();

    history.push(currentTrack->data);

    cout << "=> Now playing: " << currentTrack->data.getTitle()
         << " - "              << currentTrack->data.getArtist()
         << " ("               << currentTrack->data.getDuration() << "s)" << endl;
}

// Go to the previous song in the CDLL
void Playlist::previousSong(){
    if (head == nullptr){
        cout << "Playlist is empty!" << endl;
        return;
    }

    if (currentTrack == nullptr){
        currentTrack = tail;
    } else {
        currentTrack = currentTrack->prev;
    }

    // NEW: moving backward in playlist invalidates go-forward history
    forward.clear();

    history.push(currentTrack->data);

    cout << "=> Now playing: " << currentTrack->data.getTitle()
         << " - "              << currentTrack->data.getArtist()
         << " ("               << currentTrack->data.getDuration() << "s)" << endl;
}

// ===================================================================
// History display — unchanged
// ===================================================================
void Playlist::viewHistory() const{
    history.displayHistory();
}

// ===================================================================
// Go Back — CHANGED:
//   Old: pop current and discard it.
//   New: pop current, push it onto ForwardStack, then peek the
//        previous song so it can be restored via Go Forward.
// ===================================================================
void Playlist::goBack(){
    if (history.isEmpty()){
        cout << "No history - nothing to go back to." << endl;
        return;
    }

    // Only one entry means we are at the very first song ever played.
    // Move it to forward so Go Forward can restore it.
    if (history.size() == 1){
        Song current = history.pop();
        forward.push(current);
        currentTrack = nullptr;
        cout << "No previous song in history. (Press Go Forward to return to it.)" << endl;
        return;
    }

    // --- Normal case ---
    // 1. Pop the song currently on top (= song we are leaving)
    Song leavingSong = history.pop();

    // 2. Save it to ForwardStack so Go Forward can restore it
    forward.push(leavingSong);

    // 3. The song now on top of history is the one we are returning to
    Song prevSong = history.peek();

    cout << "=> Going back to: " << prevSong.getTitle()
         << " - "                << prevSong.getArtist()
         << " ("                 << prevSong.getDuration() << "s)" << endl;

    // 4. Sync currentTrack pointer in the CDLL
    if (head == nullptr) return;
    Node* cur = head;
    do{
        if (cur->data.getTitle()  == prevSong.getTitle() &&
            cur->data.getArtist() == prevSong.getArtist()){
            currentTrack = cur;
            break;
        }
        cur = cur->next;
    } while (cur != head);
}

// ===================================================================
// Go Forward — NEW:
//   Pop the top of ForwardStack and push it back onto HistoryStack,
//   then sync currentTrack so the CDLL pointer stays consistent.
// ===================================================================
void Playlist::goForward(){
    if (forward.isEmpty()){
        cout << "Already at the latest song - nothing to go forward to." << endl;
        return;
    }

    // 1. Pop from ForwardStack (= song we "backed away from")
    Song nextSong = forward.pop();

    // 2. Push it back onto HistoryStack (it is now the current song)
    history.push(nextSong);

    cout << "=> Going forward to: " << nextSong.getTitle()
         << " - "                   << nextSong.getArtist()
         << " ("                    << nextSong.getDuration() << "s)" << endl;

    // 3. Sync currentTrack pointer in the CDLL
    if (head == nullptr) return;
    Node* cur = head;
    do{
        if (cur->data.getTitle()  == nextSong.getTitle() &&
            cur->data.getArtist() == nextSong.getArtist()){
            currentTrack = cur;
            break;
        }
        cur = cur->next;
    } while (cur != head);
}
