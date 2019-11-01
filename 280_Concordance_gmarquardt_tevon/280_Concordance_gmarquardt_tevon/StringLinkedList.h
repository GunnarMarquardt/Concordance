#pragma once
#include <string>
//Sorted singly linked list header for the list of words starting with a given character


using namespace std;

struct StringNode {
	string data;
	StringNode* next;
};

class StringLinkedList {
private:
	StringNode* top;
	int size;
public:
	void insert(string);
	void display();
};
