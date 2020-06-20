/* Reverse poem outputs reverse poems in forward and backward directions
 * Student Name: James Eapen
 * Date: 3/27/2019
 */

#ifndef REVERSEPOEM_H_
#define REVERSEPOEM_H_

#include <iostream>
#include "Stack.h"
using namespace std;

class ReversePoem {
public:
	ReversePoem(string poemfile);
	string getTitle() const;
	string getAuthor() const;
	string getBody() const;
	string getBodyReversed() const;
private:
	string myTitle;
	string myAuthor;
	string myBody;
	string myBodyReversed;
	Stack<string> myBodyStack = Stack<string>(1);
	friend class ReversePoemTester;
};

#endif /* REVERSEPOEM_H_ */
