#include <iostream>
#include <string>
using namespace std;


struct SLLNode {
	string word;
	SLLNode* next, * prev;
};


struct CharNode {
	char data;
	CharNode* next, * prev;
	SLLNode* sllTop, * slltracker, * sllBottom;
};


class StringLL {
private:
	SLLNode* sTop, * sBottom;
	int size;
public:
	StringLL();
	void addNodeBottom(string);
	void displayStringLL();
	SLLNode* returnTop();
};


class CharList {
private:
	CharNode* cTop, * cBottom, * tracker;
	SLLNode* sll;
	int size;
public:
	CharList();
	void insert(SLLNode*);
	bool inList(SLLNode*);
	void create(SLLNode*);
	void simpleDisplay();
	void displayOffShoot(CharNode*);
	CharNode* returnTop();
	void displayEntire(); 
	void displayCharInp(char);
	void displayStrInp(string);
};


int main() {
	int input;
	char charInput;
	string strInput;

	// create a fake linked string list to test
	StringLL s1 = StringLL();
	s1.addNodeBottom("apple");
	s1.addNodeBottom("antler");
	s1.addNodeBottom("amphetimine");
	s1.addNodeBottom("axe");
	s1.addNodeBottom("jeans");
	s1.addNodeBottom("loser");
	s1.addNodeBottom("mom");

	//create a charlist to test functionality
	CharList c1 = CharList();
	SLLNode* topTester = s1.returnTop();
	c1.create(topTester); // feed in a sorted linked list to creator

	while (1) {
		cout << endl << endl;
		cout << ">>>>>>>>>>>>>>>>>>>>>" << endl;
		cout << "Choose Your Function:" << endl;
		cout << "<<<<<<<<<<<<<<<<<<<<<" << endl;
		cout << "1.Display the entire concordance" << endl;
		cout << "2.Display all words that begin with a user input letter" << endl;
		cout << "3.Display the existence of a particular user input word" << endl;
		cout << "4.Quit" << endl;
		cout << "Enter your choice: ";
		cin >> input;

		switch (input) {
		case 1:
			c1.displayEntire();
			break;
		case 2:
			cout << "Enter the char you want to look up: ";
			cin >> charInput;
			c1.displayCharInp(charInput);
			break;
		case 3:
			cout << "Enter the string you want to search: ";
			cin >> strInput;
			c1.displayStrInp(strInput);
			break;
		case 4:
			cout << "Program Terminated!" << endl;
			exit(0);
		}
	}
	return 0;
}


// ----------------- StringLL Tester Functions ----------------------------- //
StringLL::StringLL() {
	sTop = sBottom = nullptr;
	size = 0;
}


void StringLL::addNodeBottom(string request) {
	SLLNode* p = new SLLNode;
	p->word = request;
	p->prev = sBottom;
	p->next = nullptr;
	if (size == 0)
		sTop = p;
	else
		sBottom->next = p;
	sBottom = p;
	size++;
}


void StringLL::displayStringLL() {
	SLLNode* runner = sTop;
	while (runner != nullptr) {
		cout << runner->word << endl;
		runner = runner->next;
	}
}


SLLNode* StringLL::returnTop() {
	SLLNode* p = sTop;
	return p;
}


// -------------------- CharList Functions ---------- //
CharList::CharList() {
	cTop = cBottom = nullptr;
	sll = nullptr;
	size = 0;
}

bool CharList::inList(SLLNode* ptr) {
	CharNode* runner = cTop;
	while (runner != nullptr) {
		if (runner->data == ptr->word.front())
			return true;
	}
	return false;
}

// correctly sets up linked list with char, can't link to SLL yet
void CharList::insert(SLLNode* ptr) {
	if (size == 0) {
		CharNode* p = new CharNode;
		p->data = ptr->word.front();
		p->prev = cBottom;
		p->next = nullptr;
		cTop = p;
		cBottom = p;
		tracker = p;
		size++;

		SLLNode* s = new SLLNode;
		s = ptr;

		p->sllTop = s;
		p->slltracker = p->sllTop; 
		p->sllBottom = p->slltracker->next; 
	}
	else {
		if (ptr->word.front() != cBottom->data) {
			CharNode* p = new CharNode;
			p->data = ptr->word.front();
			p->prev = cBottom;
			p->next = nullptr;
			cBottom->next = p;
			cBottom = p;
			tracker = p;
			size++;

			SLLNode* s = new SLLNode;
			s = ptr; 
			p->sllTop = s;
			p->slltracker = p->sllTop; 
			p->sllBottom = p->slltracker->next;
		}
		else {
			SLLNode* s = new SLLNode;
			s = ptr;

			tracker->slltracker->next = s; 
			tracker->slltracker = tracker->slltracker->next; 
			tracker->sllBottom = tracker->slltracker->next;
		}
	}
}


// audited, this function traverses SLL fine
void CharList::create(SLLNode* p) {
	SLLNode* runner = p;
	while (runner != nullptr) {
		insert(runner);
		runner = runner->next;
	}
}


void CharList::simpleDisplay() {
	if (size == 0) cout << "char list is empty!" << endl;
	CharNode* runner = cTop;
	while (runner != nullptr) {
		cout << runner->data << endl;
		runner = runner->next;
	}
}


void CharList::displayOffShoot(CharNode* p) {
	SLLNode* runner = p->sllTop;
	while (runner != p->sllBottom) {
		cout << runner->word << "->";
		runner = runner->next; 
	}
}


CharNode* CharList::returnTop() {
	CharNode* runner = cTop->next;
	return runner;
}

void CharList::displayEntire() {
	CharNode* runner = cTop;
	while (runner != nullptr) {
		cout << runner->data << "-> ";
		displayOffShoot(runner); 
		cout << endl << "|" << endl; 
		runner = runner->next; 
	}
}

void CharList::displayCharInp(char input) {
	CharNode* runner = cTop;
	while (runner != nullptr) {
		if (runner->data == input) {
			displayOffShoot(runner);
		}
		runner = runner->next;
	}
}


void CharList::displayStrInp(string input) {
	CharNode* runner = cTop;
	while (runner != nullptr) {
		if (runner->data == input.front()) {
			SLLNode* sllRunner = runner->sllTop; 
			while (sllRunner != runner->sllBottom) {
				if (sllRunner->word == input) cout << sllRunner->word << "->";
				sllRunner = sllRunner->next; 
			}
		}
		runner = runner->next; 
	}
}
