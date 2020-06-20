/* main.cpp
 * Student Name: James Eapen
 * Date: 3/26/2019
 */
#include "StackTester.h"
#include "ReversePoem.h"
#include "ReversePoemTester.h"
#include <iostream>
using namespace std;

int main() {
	StackTester st;
	st.runTests();
	ReversePoemTester rt;
	rt.runTests();

	cout << "\nEnter the name of the poem file: ";
	string poemFile;
	cin >> poemFile;

	ReversePoem reversePoem(poemFile);
	reversePoem.getBodyReversed();
	cout << reversePoem.getTitle() << "\n"
	   << reversePoem.getAuthor() << "\n"
	   << "\n*** Top-To-Bottom ***\n\n"
	   << reversePoem.getBody()
	   << "\n\n*** Bottom-To-Top ***\n\n"
	   << reversePoem.getBodyReversed()
	   << endl;
}



