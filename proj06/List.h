/* List.h provides a class for making lists
 * Student: James Eapen
 * Date: 3/11/2019
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */


#ifndef LIST_H_
#define LIST_H_
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;

template <class Item>

class List {
public:
	List();
	List(const List<Item>& original);
	unsigned getSize() const;
	Item getFirst() const;
	Item getLast() const;
	int getIndex(const Item& it);
	void append(const Item& it);
	List<Item>& operator=(const List<Item>& original);
	bool operator==(List<Item>& original);
	bool operator!=(List<Item>& original);
	void readFrom(istream& in);
	void readFrom(string filename);
	void writeTo(ostream& out, string sep) const;
	void writeTo(string filename) const;
	void prepend(const Item& it);
	void insert(const Item& it, unsigned index);
	bool insertBefore(const Item& otherItem, const Item& item);
	bool insertAfter(const Item& otherItem, const Item& item);

	~List();

private:
	struct Node {
		Node();
		Node(Item it, Node* next);
		Item myItem;
		Node* myNext;
		~Node();
	};

	unsigned mySize;
	Node* myFirst;
	Node* myLast;

	void copy(const List<Item>& original);
	void destroy();
	void reader(const std::__cxx11::string& input,
			 std::__cxx11::string& token, double num);

	friend class ListTester;
};



/*Default constructor
 *
 */
template <class Item>
List<Item>::List() {
	mySize = 0;
	myFirst = myLast = NULL;
}

/*Copy method
 * @param: the list to be copied
 * @precondition: *this list; it may be empty or contain data
 * @postcondition: *this list is a copy of the original list
 */
template <class Item>
void List<Item>::copy(const List& original) {
	Node* oPtr = original.myFirst;
	while (oPtr != NULL) {
		append(oPtr->myItem);
		oPtr = oPtr->myNext;
	}
}
/*main list copy method
 * @param: list to be copied
 *
 */
template <class Item>
List<Item>::List(const List& original) {
	myFirst = myLast = NULL;
	mySize = 0;
	copy(original);
}

/* Default node constructor
 *
 */
template <class Item>
List<Item>::Node::Node() {
	myItem = 0;
	myNext = NULL;
}

/* Explicit node constructor
 * @param: Item, node pointer
 */
template <class Item>
List<Item>::Node::Node(Item it, Node* next) {
	myItem = it;
	myNext = next;
}

/*Return size of the list
 *
 */
template <class Item>
unsigned List<Item>::getSize() const{
	return mySize;
}

/*Retrieve the first item in the list
 * Returns: first item
 */
template <class Item>
Item List<Item>::getFirst() const{
	if (mySize < 0 or myFirst == NULL) {
		throw underflow_error("Underflow error");
	}
	else {
		return myFirst->myItem;
	}
}

/*Retrieve the last item in the list
 * Returns: last item
 */
template <class Item>
Item List<Item>::getLast() const {
	if (mySize < 0 or myLast == NULL) {
		throw underflow_error("Underflow error");
	}

	else {
		return myLast->myItem;
	}
}
template <class Item>
int List<Item>::getIndex(const Item& it) {
	unsigned index = 0;
	Node* iPtr = myFirst;
	if (iPtr->myItem == it) {
		return index;
	}
	else {
		for (unsigned i = 0; i < mySize; ++i) {
			if (iPtr->myItem == it) {
				return index;
			}
			else iPtr = iPtr->myNext;
			++index;
		}
	}
	return -1;
}


/* Append method
 * @param: item to be appended
 * @pre-condition: list size is n, does not contain the new item
 * @postcondition: the new item is added in dynamic memory, list size is one greater
 */
template <class Item>
void List<Item>::append(const Item& it) {
	mySize += 1;
	Node *newnode = new Node(it, NULL);

	if (mySize < 0 or myFirst == NULL) {
		myFirst = myLast = newnode;
	}

	else {
		myLast->myNext = newnode;
		myLast = newnode;
	}

}

/* Assignment method - assigns a list to another list
 * @param: the list to be assigned to another
 * Returns: a copy of the original list
 */
template <class Item>
List<Item>& List<Item>::operator=(const List& original) {
	if (original.myFirst == myFirst and original.myLast == myLast) {
		return *this;
	}

	destroy();
	copy(original);
	return *this;
}

/*Equality tester
 * @author: James Eapen
 * @param: List to be checked against
 * Returns bool true or false
 */
template <class Item>
bool List<Item>::operator==(List& original) {
	Node* myPtr = myFirst;
	Node* ogPtr = original.myFirst;
	if (mySize == original.mySize) {
		if (myFirst->myItem == original.myFirst->myItem and myLast->myItem == original.myLast->myItem) {
			while (myPtr != NULL) {
				if (myPtr->myItem == ogPtr->myItem) {
					myPtr = myPtr ->myNext;
					ogPtr = ogPtr ->myNext;
				}
				else return false;
			}
		}
		else return false;
	}
	else return false;
	return true;
}

/* Inequality tester
 * @author: James Eapen
 * @param: List to be checked against
 * Returns true or false based on check
 */
template <class Item>
bool List<Item>::operator!=(List& original) {
	return !(*this == original);
}

/* Reader method for read from stream and read from filename
 * @author: James Eapen
 * @param: input string from getline, token string and double num variable to store the values in
 * @precondition: list may contain items
 * @postcondition: list was cleared and data added from the string input
 */
template <class Item>
void List<Item>::reader(const string& input, string& token, double num) {
	destroy();
	stringstream ss(input);
	while (ss >> token) {
		num = atoi(token.c_str());
		append(num);
	}
}

/* Read from stream method
 * @author: James Eapen
 * @param: istream
 * @precondition: istream contains the data for the list
 * @postcondition: istream data is read into the list
 */
template <class Item>
void List<Item>::readFrom(istream& in) {
	string input, token;
	double num;
	getline(in, input);
	reader(input, token, num);

}

/* Read from file method
 * @author: Jame Eapen
 * @param: filename
 * @precondition: filename is passed in
 * @postcondition: list contains data in the file
 */
template <class Item>
void List<Item>::readFrom(string filename) {
	ifstream fin (filename.c_str());
	string input, token;
	double num;
	getline(fin, input);
	reader(input, token, num);
}

/* Write to stream method
 * @author: James Eapen
 * @param: ostream
 * @precondition: ostream is passed in
 * @postcondition: ostream contains list data
 */
template <class Item>
void List<Item>::writeTo(ostream& out, string sep) const{
	Node* Ptr = myFirst;
	out << myFirst->myItem << flush;
	Ptr = myFirst->myNext;
	while (Ptr != NULL) {
		out << sep << Ptr->myItem << flush;
		Ptr = Ptr->myNext;
	}

}

/* << overloader for output to cout
 * @author: James Eapen
 * @param: ostream, list to be output
 * Returns: ostream containing list data
 */
template <class Item>
ostream& operator<<(ostream& out, const List<Item>& list) {
	list.writeTo(out, "=");
	return out;

}

/* Write to file method
 * @author: James Eapen
 * @param: filename
 * @precondition: filename is passed into function
 * @postcondition: file contains list data
 */
template <class Item>
void List<Item>::writeTo(string filename) const{
	ofstream out(filename.c_str());
	Node* Ptr = myFirst;
	out << myFirst->myItem << "\t" << flush;
	Ptr = myFirst->myNext;
	while (Ptr != NULL) {
		out << Ptr->myItem << "\t" << flush;
		Ptr = Ptr->myNext;
	}
}

/* Prepend method
 * @author: James Eapen
 * @param: Item to be added to list
 * @precondition: list is of size, and the first item is the item at myFirst
 * @postcondition: list is of size +1 and the first item is it
 */
template <class Item>
void List<Item>::prepend(const Item& it) {
	myFirst = new Node(it, myFirst);

	if (mySize == 0) {
		myLast = myFirst;
	}
	mySize++;
}

/* Insertion method
 * @author: James Eapen
 * @param: item, index
 * @precondition: list has another item or nothing at the index
 * @postcondition: list has item it at index and the previous item->myNext is chaned to the new Item
 */
template <class Item>
void List<Item>::insert(const Item& it, unsigned index) {
	if (index > mySize) {
		throw invalid_argument("Out of range");
	}
	else if (index == 0) {
		prepend(it);
	}
	else {
		Node* iPtr = myFirst->myNext;
		Node* prev = myFirst;
		for (unsigned i = 0; i < index-1; ++i) {
			prev = iPtr;
			iPtr = iPtr->myNext;
		}
		Node* newPtr = new Node(it, iPtr);
		prev->myNext = newPtr;
		mySize += 1;
	}
}

/* Relative insertion method
 * @author: James Eapen
 * @param: item, item to be inserted after
 * @precondition: list contains other item but not item after it
 * @postcondition: list contains item after other item
 */
template <class Item>
bool List<Item>::insertAfter(const Item& otherItem, const Item& item) {
	int i = getIndex(otherItem);
	if (i == -1) {
		return false;
	}
	else {
	insert(item, i+1);
	return true;
	}
}

/* Relative insertion method
 * @author: James Eapen
 * @param: item 
 * @precondition: list contains other item but not item before it
 * @postcondition: list contains item after other item
 */
template <class Item>
bool List<Item>::insertBefore(const Item& otherItem, const Item& item) {
	int i = getIndex(otherItem);
	if (i == -1) {
		return false;
	}
	else {
	insert(item, i);
	return true;
	}
}

/*Destructor method
 *
 */
template <class Item>
void List<Item>::destroy() {
	   delete myFirst;          // delete first node, invoking ~Node() (does nothing if myFirst == NULL)
	   myFirst = myLast = NULL; // clear myFirst and myLast (optional)
	   mySize = 0;              // clear mySize (optional)
}

/* List destructor
 *
 */
template <class Item>
List<Item>::~List() {
	destroy();
}

/* Node destructor
 *
 */
template <class Item>
List<Item>::Node::~Node() {
//	cout << "~Node() is deallocating the node containing item " << myItem << endl;
   delete myNext;       // delete the next node, invoking ~Node() in it
                        // (does nothing if myNext == NULL)
}


#endif /* LIST_H_ */
