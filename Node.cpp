#include "Node.h"

Node::Node(const Song& song){
	data = song;
	next = nullptr;
};