/* Stack.cpp defines the dynamically allocated (array-based ) Stack operations.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name: James Eapen
 * Date: 3/26/2019
 */

#include "Stack.h"

/* explicit-value constructor
 * Parameter: capacity, an unsigned value.
 * Precondition: capacity > 0.
 * Postcondition: mySize == 0 && myCapacity == capacity
 *              && myArray contains the address of a dynamic array of 'capacity' entries.
 */
Stack::Stack(unsigned capacity) {
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
Stack::Stack(const Stack& original) {
	makeCopyOf(original);
}

/* utility method containing code refactored from
 *  the copy constructor and operator=.
 * Parameter: original, a Stack (const reference).
 * Precondition: original.myCapacity > 0.
 * Postcondition: I am a copy of original.
 */
void Stack::makeCopyOf(const Stack& original) {
	myCapacity = original.myCapacity;
	myArray = new Item[myCapacity];

	for (unsigned i = 0; i < myCapacity; i++) {
		myArray[i] = original.myArray[i];
	}
	mySize = original.mySize;
}

/* Size checker to check if the stack is empty
 * return: true if the stack is empty
 */
bool Stack::isEmpty() const{
	if (mySize == 0) {
		return true; }
	else return false;
}

/* Size checker to check if the stack is full
 * return: true if the stack is full
 */
bool Stack::isFull() const {
	if (mySize == myCapacity) {
		return true; }
	else return false;
}

/* Append item to top of stack
 * @postcondition: stack is size+1 and it is at the top
 */
void Stack::push(const Item& it) {
	if (mySize == myCapacity) {
		throw StackException("push():", "stack is full");
	}
	myArray[mySize] = it;
	++mySize;
}

/* Remove and return the top item
 * Return: the top item
 */
Item& Stack::pop() {
	if (mySize == 0) {
		throw StackException("pop():", "stack is empty");
	}
	mySize = mySize - 1;
	return myArray[mySize];
}

/* Return the top item in the stack
 *
 */
Item& Stack::peekTop() const {
	if ( isEmpty( ) ) {
		throw StackException("peekTop()", "stack is empty");
	}
	return myArray[mySize-1];
}

/* destructor
 * Postcondition: myCapacity == 0 && mySize == 0
 *             && myArray has been deallocated.
 */
Stack::~Stack() {
	delete [] myArray;
	myArray = NULL;
	myCapacity = 0;
	mySize = 0;
}

/* assignment operator
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original
 *              && I have been returned.
 */
Stack& Stack::operator=(const Stack& original) {
	if (this != &original) {
		delete [] myArray;
		makeCopyOf(original);
	}
	return *this;
}

