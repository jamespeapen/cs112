/* Reverse poem outputs reverse poems in forward and backward directions
 * Student Name: James Eapen
 * Date: 3/27/2019
 */


#include "ReversePoem.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

/* Constructor method
 * @param: poem file name
 * Reads title, author and body, storing the body in a string and in a stack.
 * The reverse is popped into a string from the stack.
 */
ReversePoem::ReversePoem(string poemfile) {
	string line;
	ifstream fin(poemfile.c_str());
	getline(fin, myTitle);
	getline(fin, myAuthor);
	getline(fin, line);	//third line is blank
	while (true) {
		if (fin.eof()) { break;
		}
		getline(fin, line);
		try {
			myBodyStack.push(line);
		} catch (StackException& se) {
			myBodyStack.setCapacity((myBodyStack.getCapacity()*2));	//double stack capacity
			myBodyStack.push(line);
		}
		myBody = myBody + line + "\n";	//poem forwards

	}
	fin.close();

	unsigned size = myBodyStack.getSize();
	for (unsigned i = 0; i < size; ++i) {
		myBodyReversed = myBodyReversed + myBodyStack.pop() + "\n";	//poem reversed
	}
}

/*Returns title
 *
 */
string ReversePoem::getTitle() const {
	return myTitle;
}

/*Returns author
 *
 */
string ReversePoem::getAuthor() const {
	return myAuthor;
}

/*Returns body forwards
 *
 */
string ReversePoem::getBody() const{
	return myBody;
}

/*Returns body in reverse
 *
 */
string ReversePoem::getBodyReversed() const{
	return myBodyReversed;
}
