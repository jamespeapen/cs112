/* LinkedQueue.cpp defines the methods for class LinkedQueue.
 * Joel Adams, for CS 112 at Calvin College.
 * Student name: James Eapen
 * Date: 4/5/19
 */

#include "LinkedQueue.h"

/* Default constructor
 *
 */
LinkedQueue::LinkedQueue() {
	mySize = 0;
	myFirstPtr = myLastPtr = NULL;
}

/* Copy Constructor
 * @param: a linked queue
 *
 */
LinkedQueue::LinkedQueue(const LinkedQueue& original) {
	makeCopyOf(original);
}

/* Makes a copy of a queue
 * @param: queue to be copied
 * @postcondition: queue is deep copied to another queue
 */
void LinkedQueue::makeCopyOf(const LinkedQueue& original) {
	mySize = original.mySize;
	if ( mySize == 0 ) {
		myFirstPtr = myLastPtr = NULL;
	} else {
		myFirstPtr = new Node(original.getFirst(), NULL);
		Node * temp0 = original.myFirstPtr->myNextPtr;
		Node * temp1 = myFirstPtr;
		while (temp0 != NULL) {
			temp1->myNextPtr = new Node(temp0->myItem, NULL);
			temp1 = temp1->myNextPtr;
			temp0 = temp0->myNextPtr;
		}
		myLastPtr = temp1;
	}
}

/* Returns first item in the queue
 *
 */
Item& LinkedQueue::getFirst() const {
	if (mySize == 0) {
		throw EmptyQueueException("LinkedQueue::getFirst");
	}
	else return myFirstPtr->myItem;
}

/* Returns last item in the queue
 *
 */
Item& LinkedQueue::getLast() const {
	if (mySize == 0) {
		throw EmptyQueueException("LinkedQueue::getFirst");
	}
	else return myLastPtr->myItem;
}

/* Append method
 * @param: Item
 * @postcondition: Queue contains another node with Item
 */
void LinkedQueue::append(const Item& it) {
	try {
		Node* nPtr = new Node(it, NULL);
		if (mySize == 0) {
			myFirstPtr = nPtr;
			myLastPtr = nPtr;
			++mySize;
		}
		else {
		myLastPtr->myNextPtr = nPtr;
		myLastPtr = nPtr;
		++mySize;
		}
	}
	catch (std::bad_alloc&) {
		throw FullQueueException("LinkedQueue::append(): ");
	}
}

/* Remove method
 * @postcondition: queue does not contain its first item and mySize is reduced by 1
 * @returns: first item in queue
 */
Item LinkedQueue::remove() {
	if (mySize == 0) {
		throw EmptyQueueException("LinkedQueue::remove(): ");
	}
	else {
		Item result = myFirstPtr->myItem;
		Node* tmp = myFirstPtr;
		myFirstPtr = myFirstPtr->myNextPtr;
		tmp->myNextPtr = NULL;
		delete tmp;
		--mySize;
		return result;
	}
}

/* Destructor method
 *
 */
LinkedQueue::~LinkedQueue() {
	delete myFirstPtr;
	myFirstPtr = myLastPtr = NULL;
	mySize = 0;
}

/* Assignment operator
 * @param: the queue to be assigned as
 * @postcondition: queue is the same as original through deep copy
 */
LinkedQueue& LinkedQueue::operator=(const LinkedQueue& aQueue) {
	if (this != &aQueue) {
		delete myFirstPtr;    // invokes recursive ~Node()
		makeCopyOf(aQueue);
	}
	return *this;
}
