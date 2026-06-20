#include "Song.h"
#include <iostream>
using namespace std;
Song::Song(){
	title = "";
	artist = "";
	duration = 0; // tính theo số giây
}
Song::Song(const string& t, const string& a, int d){
	this->title = t;
	this->artist = a;
	this->duration = d;
    }
string Song::getTitle() const{
	return title;
}
string Song::getArtist() const{
	return artist;
}
int Song::getDuration() const{
	return duration;
}
void Song::setTitle(const string& t){
	this->title = t;
}
void Song::setArtist(const string& a){
	this->artist = a;
}
void Song::setDuration(int d){
	this->duration = d;
    }