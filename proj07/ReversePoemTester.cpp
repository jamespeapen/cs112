/* Tester for ReversePoem class
 * Student Name: James Eapen
 * Date: 3/27/2019
 */

#include "ReversePoemTester.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <ostream>
using namespace std;

ReversePoemTester::ReversePoemTester() {

}

void ReversePoemTester::runTests() {
	cout << "Testing class ReversePoem..." << endl;
	testConstructor();
	testGetTitleGetAuthor();
	testGetBody();
	testGetBodyReversed();
	cout << "All tests passed!" << endl;
}

void ReversePoemTester::testConstructor() {
	cout << "- Testing Constructor..." << flush;
	ReversePoem r("poems/cats.txt");
	assert(r.myBodyStack.getCapacity() == 4); //three lines in the poem
	cout << " 1 " << flush;
	assert(r.myBodyStack.getSize() == 0); //stack should be empty after all lines are popped into the reverseBody
	cout << " 2 " << flush;
	cout << "Passed!" << endl;
}

void ReversePoemTester::testGetTitleGetAuthor() {
	cout << "- Testing getTitle()..." << flush;
	ReversePoem r("poems/love.txt");
	assert( r.getTitle() == "Love?");
	cout << " 1 " << flush;
	cout << "Passed!" << endl;
	cout << "- Testing getAuthor()..." << flush;
	assert( r.getAuthor() == "Anonymous");
	cout << " 1 " << flush;
	cout << "Passed!" << endl;
}

void ReversePoemTester::testGetBody() {
	cout << "- Testing getBody()..." << flush;
	ReversePoem r("poems/cats.txt");
	ofstream fout("testGetBody.txt");
	assert( fout.is_open());
	fout << r.getBody();
	fout.close();
	cout << " 0 " << flush;
	ifstream fin("testGetBody.txt");
	string line;
	getline(fin, line);
	assert(line == "I love it when cats rub against me.");
	cout << " 1 " << flush;
	getline(fin, line);
	assert(line == "I could never say");
	cout << " 2 " << flush;
	getline(fin, line);
	assert(line == "I hate those purring felines.");
	cout << " 3 " << flush;
	fin.close();
	cout << "Passed!" << endl;
}

void ReversePoemTester::testGetBodyReversed() {
	cout << "- Testing getBodyReversed()..." << flush;
	ReversePoem r("poems/cats.txt");
	ofstream fout("testGetBodyReversed.txt");
	assert( fout.is_open());
	fout << r.getBodyReversed();
	fout.close();
	cout << " 0 " << flush;
	ifstream fin("testGetBodyReversed.txt");
	string line;
	getline(fin, line);
	assert( line == "I hate those purring felines.");
	cout << " 1 " << flush;
	getline(fin, line);
	assert( line == "I could never say");
	cout << " 2 " << flush;
	getline(fin, line);
	assert( line == "I love it when cats rub against me.");
	cout << " 3 " << flush;
	fin.close();
	cout << "Passed!" << endl;
}
