/* ArrayQueue.cpp defines the methods for class ArrayQueue.
 * Joel Adams, for CS 112 at Calvin College.
 * Student name: James Eapen
 * Date: 4/5/19
 */

#include "ArrayQueue.h"
#include <cstring>  // memcpy()
#include <iostream>
using namespace std;

/* Constructor
 * @param: capacity
 * postcondition: array created with capacity
 */
ArrayQueue::ArrayQueue(unsigned capacity) {
	if (capacity < 1) {
		throw QueueException("ArrayQueue::ArrayQueue(): ", "capacity cannot be zero");
	}
	myCapacity = capacity;
	mySize = 0;
	myFirstIndex = 0;
	myLastIndex = capacity -1;
	myArrayPtr = new Item[capacity];
}

/* copy constructor
 * @param: original, the ArrayQueue to be copied.
 * Postcondition: I am a deep copy of original.
 */
ArrayQueue::ArrayQueue(const ArrayQueue& original) {
	makeCopyOf(original);
}

/* utility method to build copies
 * @param: original, the ArrayQueue to be copied.
 * Postcondition: I am a deep copy of original.
 */
void ArrayQueue::makeCopyOf(const ArrayQueue& original) {
	mySize = original.mySize;
	myCapacity = original.myCapacity;
	myFirstIndex = original.myFirstIndex;
	myLastIndex = original.myLastIndex;
	myArrayPtr = new Item[myCapacity];
	memcpy(myArrayPtr, original.myArrayPtr, myCapacity*sizeof(Item) );
}

/* destructor
 * Postcondition: my dynamic array has been deallocated.
 */
ArrayQueue::~ArrayQueue() {
	delete [] myArrayPtr;
	myArrayPtr = NULL;
	mySize = myFirstIndex = myLastIndex = 0;
}

/* assignment operator
 * @param: aQueue, an ArrayQueue/
 * @return: myself.
 * Postcondition: I am a deep copy of aQueue.
 */
ArrayQueue& ArrayQueue::operator=(const ArrayQueue& aQueue) {
	if (this != &aQueue) {
		delete [] myArrayPtr;
		makeCopyOf(aQueue);
	}
	return *this;
}


/* accessor for myCapacity
 * @return myCapacity.
 */
unsigned ArrayQueue::getCapacity() const {
	return myCapacity;
}

/* accessor for mySize
 * @return mySize.
 */
unsigned ArrayQueue::getSize() const {
	return mySize;
}

/* Am I empty?
 * @return: true if I am empty, false othewise.
 */
bool ArrayQueue::isEmpty() const {
	return mySize == 0;
}

/* Am I full?
 * @return: true if I am full, false othewise.
 */
bool ArrayQueue::isFull() const {
	return getSize() == myCapacity;
}

/*First item getter
 * @return: first item in array queue
 */
Item& ArrayQueue::getFirst() const{
	if (mySize == 0) {
			throw EmptyQueueException("ArrayQueue::getFirst(): ");
		}
	else return myArrayPtr[myFirstIndex];
}

/* Last item getter
 * @return: last item in array queue
 */
Item& ArrayQueue::getLast() const{
	if (mySize == 0) {
			throw EmptyQueueException("ArrayQueue::getLast(): ");
		}
	else return myArrayPtr[myLastIndex];
}

/* Append it to queue
 * @param: Item it;
 * @postcondition: it is at the end of the queue
 */
void ArrayQueue::append(const Item& it) {
	if ( !(isFull()) ) {
		myLastIndex = (myLastIndex+1) % myCapacity;
		myArrayPtr[myLastIndex] = it;
		++mySize;
	}
	else throw FullQueueException("append(): ");
}

/* Remove method
 * Postcondition: mySize is mySize-1 and myFirstIndex is incremented by one
 * 				(wrapped around myCapacity)
 * Returns the oldest item in the array
 */
Item ArrayQueue::remove() {
	Item tmp;
	if (mySize == 0) {
		throw EmptyQueueException("ArrayQueue::remove(): ");
	}
	else {
		tmp = myArrayPtr[myFirstIndex];
		myFirstIndex = (myFirstIndex+1)%myCapacity;
		--mySize;
		return tmp;
	}
}
