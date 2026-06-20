#ifndef PLAYLISH_H
#define PLAYLISH_H
#include "Node.h"
#include <string>

class Playlist{
	private:
		Node* head;
		Node* tail;
		int size;
		Node* currentTrack;
	public:
		Playlist();
		
		void addSong(const Song&song);
		void removeSong(int position);
		void updateSong(int position);
		void displayPlaylist() const;
		void searchSong(const string& keyword);
		
		void saveToFile() const;
    	void loadFromFile();
    	void clear();
		
		
    	bool isEmpty() const;
    	int getSize() const;
};
#endif