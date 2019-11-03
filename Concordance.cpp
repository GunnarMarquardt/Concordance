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
};

int main() {
	int input;
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

	c1.create(topTester);

	CharNode* topCharTester = c1.returnTop();
	cout << "topCharTester = " << topCharTester->data << endl; 
	c1.displayOffShoot(topCharTester); 

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
			cout << "This isn't built yet!" << endl;
			break;
		case 3:
			cout << "This isn't built yet!" << endl;
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
	cout << "Insert has began = " << ptr->word << endl << endl;
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

		cout << "initial sll = " << p->slltracker->word << endl;
		cout << "first Node data = " << p->data << endl;
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

			cout << "sll embedded = " << p->slltracker->word << endl;
		}
		else {
			cout << "it got this far = " << ptr->word << endl;
			SLLNode* s = new SLLNode;
			s = ptr;

			tracker->slltracker->next = s; 
			tracker->slltracker = tracker->slltracker->next; 
			cout << "else clause sll =  " << tracker->slltracker->word << endl;
			tracker->sllBottom = tracker->slltracker->next;

			cout << "the bottom is = " << tracker->sllBottom->word << endl; 
		}
	}
}


// audited, this function traverses SLL fine
void CharList::create(SLLNode* p) {
	SLLNode* runner = p;
	int i = 0;
	while (runner != nullptr) {
		cout << "create loop " << i << ": " << endl << endl;
		insert(runner);
		runner = runner->next;
		i++; 
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