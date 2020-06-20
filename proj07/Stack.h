/* Stack.h provides a (dynamic-array-based) Stack class.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name: James Eapen
 * Date: 3/26/2019
 * 
 * Invariant: mySize == 0 && isEmpty() && !isFull()
 *         || mySize == myCapacity && !isEmpty() && isFull()
 *         || mySize > 0 && mySize < myCapacity && !isEmpty() && !isFull().
 * Notes: 
 * 1. Member mySize always contains the index of the next empty space in myArray
 *        (the index of the array element into which the next pushed item will be placed).
 * 2. Sending push() to a full Stack throws the exception Stack::Overflow.
 * 3. Sending pop() or peekTop() to an empty Stack throws the exception Stack::Underflow.
 */

#ifndef STACK_H_
#define STACK_H_

#include "StackException.h"
#include <string>
#include <iostream>
using namespace std;

template <class Item>

class Stack {
public:
	Stack(unsigned capacity);
	Stack(const Stack<Item>& original);
	unsigned getCapacity() const;
	void setCapacity(const unsigned& capacity);
	unsigned getSize() const;
	bool isEmpty() const;
	bool isFull() const;
	Stack<Item>& operator=(const Stack<Item>& original);
	void push(const Item& it);
	Item& pop();
	Item& peekTop() const;
	~Stack();

	
protected:
	void makeCopyOf(const Stack<Item>& original);
	
private:
	unsigned myCapacity;
	unsigned mySize;
	Item*    myArray;
	friend class StackTester;
};

/* explicit-value constructor
 * Parameter: capacity, an unsigned value.
 * Precondition: capacity > 0.
 * Postcondition: mySize == 0 && myCapacity == capacity
 *              && myArray contains the address of a dynamic array of 'capacity' entries.
 */
template <class Item>
Stack<Item>::Stack(unsigned capacity) {
	if (!(capacity > 0 )) {
		throw StackException("Stack(capacity):", "capacity must be positive");
	}
	mySize = 0;
	myCapacity = capacity;
	myArray = new Item[capacity];
}

/* copy constructor
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original.
 */
template <class Item>
Stack<Item>::Stack(const Stack<Item>& original) {
	makeCopyOf(original);
}

/* utility method containing code refactored from
 *  the copy constructor and operator=.
 * Parameter: original, a Stack (const reference).
 * Precondition: original.myCapacity > 0.
 * Postcondition: I am a copy of original.
 */
template <class Item>
void Stack<Item>::makeCopyOf(const Stack<Item>& original) {
	myCapacity = original.myCapacity;
	myArray = new Item[myCapacity];

	for (unsigned i = 0; i < myCapacity; i++) {
		myArray[i] = original.myArray[i];
	}
	mySize = original.mySize;
}

/* Returns stack capacity
 *
 */
template <class Item>
unsigned Stack<Item>::getCapacity() const {
	return myCapacity;
}

/* Set stack capacity
 * Postcondition: the stack capacity is changed and old data copied into the new stack
 */
template <class Item>
void Stack<Item>::setCapacity(const unsigned& capacity) {
	if (capacity < mySize or capacity == 0) {
		throw StackException("setCapacity()", "capacity too low, data may be lost");
	}
	Item* newArray = new Item[capacity];
	for (unsigned i = 0; i < mySize; ++i) {
		newArray[i] = myArray[i];
	}
	delete [] myArray;
	myArray = newArray;
	myCapacity = capacity;
}

/* Returns number of items in stack
 *
 */
template <class Item>
unsigned Stack<Item>::getSize() const {
	return mySize;
}

/* Size checker to check if the stack is empty
 * return: true if the stack is empty
 */
template <class Item>
bool Stack<Item>::isEmpty() const{
	if (mySize == 0) {
		return true; }
	else return false;
}

/* Size checker to check if the stack is full
 * return: true if the stack is full
 */
template <class Item>
bool Stack<Item>::isFull() const {
	if (mySize == myCapacity) {
		return true; }
	else return false;
}

/* assignment operator
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original
 *              && I have been returned.
 */
template <class Item>
Stack<Item>& Stack<Item>::operator=(const Stack<Item>& original) {
	if (this != &original) {
		delete [] myArray;
		makeCopyOf(original);
	}
	return *this;
}

/* Append item to top of stack
 * @postcondition: stack is size+1 and it is at the top
 */
template <class Item>
void Stack<Item>::push(const Item& it) {
	if (mySize == myCapacity) {
		throw StackException("push():", "stack is full");
	}
	myArray[mySize] = it;
	++mySize;
}

/* Remove and return the top item
 * Return: the top item
 */
template <class Item>
Item& Stack<Item>::pop() {
	if (mySize == 0) {
		throw StackException("pop():", "stack is empty");
	}
	mySize -= 1;
	return myArray[mySize];
}

/* Return the top item in the stack
 *
 */
template <class Item>
Item& Stack<Item>::peekTop() const {
	if ( isEmpty( ) ) {
		throw StackException("peekTop()", "stack is empty");
	}
	return myArray[mySize-1];
}

/* destructor
 * Postcondition: myCapacity == 0 && mySize == 0
 *             && myArray has been deallocated.
 */
template <class Item>
Stack<Item>::~Stack() {
	delete [] myArray;
	myArray = NULL;
	myCapacity = 0;
	mySize = 0;
}

#endif

