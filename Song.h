#ifndef SONG_H
#define SONG_H
#include <string>
using namespace std;

class Song {
	private:
		string title;
		string artist;
		int duration;
	public:
		Song();
		Song(const string& t,const string& a, int d); //Constructor
		
		string getTitle() const;
		string getArtist() const;
		int getDuration() const;
		
		void setTitle(const string& t);
		void setArtist(const string& a);
		void setDuration(int d);
};
#endif