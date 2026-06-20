#ifndef NOTE_H
#define NOTE_H
#include "Song.h"

class Node{
	public:
		Song data;
		Node* next;
		Node* prev;
		
		Node(const Song& song);
};

#endif
