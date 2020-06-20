/* ArrayQueue.h declares a Queue class using a dynamic array.
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 * Student name: James Eapen
 * Date: 4/5/19
 * 
 * Class Invariant: 
 *    mySize == 0 ||
 *    mySize > 0 && myArray[myFirst] == getFirst()
 *               && myArray[myLast] == getLast().
 * 
 *  (When I am not empty:
 *     myFirstIndex is the index of my oldest value;
 *     myLastIndex is the index of my newest value.)
 */

#ifndef ARRAY_QUEUE_H_
#define ARRAY_QUEUE_H_

#include "QueueException.h"
#include "ArrayQueue.h"
#include <cstring>  // memcpy()
#include <iostream>
using namespace std;

template <class Item>
class ArrayQueue {
public:
	ArrayQueue(unsigned capacity);

	ArrayQueue(const ArrayQueue<Item>& original);
	virtual ~ArrayQueue();
	ArrayQueue<Item>& operator=(const ArrayQueue<Item>& original);
	unsigned getSize() const;
	unsigned getCapacity() const;
	bool isEmpty() const;
	bool isFull() const;
	Item& getFirst() const;
	Item& getLast() const;
	void append(const Item& it);
	Item remove();

protected:
	virtual void makeCopyOf(const ArrayQueue<Item>& original);
private:
	unsigned mySize;       // number of items I contain
	unsigned myCapacity;   // how many items I can store
	unsigned myFirstIndex; // index of oldest item (if any)
	unsigned myLastIndex;  // index of newest item (if any)
	Item*    myArrayPtr;   // dynamic array of items

	friend class ArrayQueueTester;
};


/* Constructor
 * @param: capacity
 * postcondition: array created with capacity
 */
template <class Item>
ArrayQueue<Item>::ArrayQueue(unsigned capacity) {
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
template <class Item>
ArrayQueue<Item>::ArrayQueue(const ArrayQueue<Item>& original) {
	makeCopyOf(original);
}

/* utility method to build copies
 * @param: original, the ArrayQueue to be copied.
 * Postcondition: I am a deep copy of original.
 */
template <class Item>
void ArrayQueue<Item>::makeCopyOf(const ArrayQueue<Item>& original) {
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
template <class Item>
ArrayQueue<Item>::~ArrayQueue() {
	delete [] myArrayPtr;
	myArrayPtr = NULL;
	mySize = myFirstIndex = myLastIndex = 0;
}

/* assignment operator
 * @param: aQueue, an ArrayQueue/
 * @return: myself.
 * Postcondition: I am a deep copy of aQueue.
 */
template <class Item>
ArrayQueue<Item>& ArrayQueue<Item>::operator=(const ArrayQueue& aQueue) {
	if (this != &aQueue) {
		delete [] myArrayPtr;
		makeCopyOf(aQueue);
	}
	return *this;
}


/* accessor for myCapacity
 * @return myCapacity.
 */
template <class Item>
unsigned ArrayQueue<Item>::getCapacity() const {
	return myCapacity;
}

/* accessor for mySize
 * @return mySize.
 */
template <class Item>
unsigned ArrayQueue<Item>::getSize() const {
	return mySize;
}

/* Am I empty?
 * @return: true if I am empty, false othewise.
 */
template <class Item>
bool ArrayQueue<Item>::isEmpty() const {
	return mySize == 0;
}

/* Am I full?
 * @return: true if I am full, false othewise.
 */
template <class Item>
bool ArrayQueue<Item>::isFull() const {
	return getSize() == myCapacity;
}

/*First item getter
 * @return: first item in array queue
 */
template <class Item>
Item& ArrayQueue<Item>::getFirst() const{
	if (mySize == 0) {
			throw EmptyQueueException("ArrayQueue::getFirst(): ");
		}
	else return myArrayPtr[myFirstIndex];
}

/* Last item getter
 * @return: last item in array queue
 */
template <class Item>
Item& ArrayQueue<Item>::getLast() const{
	if (mySize == 0) {
			throw EmptyQueueException("ArrayQueue::getLast(): ");
		}
	else return myArrayPtr[myLastIndex];
}

template <class Item>
void ArrayQueue<Item>::append(const Item& it) {
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
template <class Item>
Item ArrayQueue<Item>::remove() {
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


#endif /*ARRAY_QUEUE_H_*/
