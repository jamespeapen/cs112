/* ListTester.cpp defines the test methods for class List.
 * Student: James Eapen
 * Date: 3/11/2019
 * Joel Adams, for CS 112 at Calvin College.
 */


#include "ListTester.h" // ListTester
#include "List.h"       // List
#include <iostream> // cin, cout
#include <fstream>
#include <cassert>      // assert()
#include <cstdlib>      // exit()
#include <stdexcept>    // underflow_error
using namespace std;

void ListTester::runTests() {
	cout << "Running List tests..." << endl;
	testDefaultConstructor();
	testNodeDefaultConstructor();
	testNodeExplicitConstructor();
	testgetIndex();
	testAppend();
	testDestructor();
	testCopyConstructor();
	testAssignment();
	testEquality();
	testInequality();
	testReadFromStream();
	testReadFromString();
	testWritetoString();
	testPrepend();
	testInsert();
	testInsertAt();
	cout << "All tests passed!" << endl;
}

void ListTester::testDefaultConstructor() {
	cout << "Testing List default constructor... " << flush;
	List<double> aList;
	assert( aList.mySize == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << "Passed!" << endl;
}

void ListTester::testNodeDefaultConstructor() {
	cout << "Testing Node default constructor... " << flush;
	List<double>::Node aNode;
	assert( aNode.myItem == double() );
	assert( aNode.myNext == NULL );
	cout << "Passed!" << endl;
}

void ListTester::testNodeExplicitConstructor() {
	cout << "Testing Node explicit constructor... " << flush;
	List<double>::Node n1(11, NULL);
	assert( n1.myItem == 11 );
	assert( n1.myNext == NULL );
	cout << " 1 " << flush;

	List<double>::Node *n3 = new List<double>::Node(33, NULL);
	List<double>::Node n2(22, n3);
	assert( n2.myItem == 22 );
	assert( n2.myNext == n3 );
	cout << " 2 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testgetIndex() {
	cout << "Testing getIndex()... " << flush;

	List<double> list0;
	list0.append(11);
	list0.append(12);
	list0.append(13);

	assert( list0.getIndex(11) == 0);
	cout << " 1 " << flush;
	assert( list0.getIndex(12) == 1);
	cout << " 2 " << flush;
	assert( list0.getIndex(13) == 2);
	cout << " 3 " << flush;
	assert( list0.getIndex(99) == -1);

	cout << "Passed!" << endl;
}

void ListTester::testAppend() {
	cout << "Testing append()... " << flush;
	// empty List
	List<double> aList;
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	try {
		aList.getFirst();
		cerr << "getFirst() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0a " << flush;
	}
	try {
		aList.getLast();
		cerr << "getLast() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0b " << flush;
	}
	// append to empty list
	aList.append(11);
	assert( aList.getSize() == 1 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast == aList.myFirst );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 11 );
	assert( aList.myFirst->myNext == NULL );
	cout << " 1 " << flush;
	// append to a list containing 1 Item
	aList.append(22);
	assert( aList.getSize() == 2 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast != NULL );
	assert( aList.myFirst != aList.myLast );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 22 );
	assert( aList.myFirst->myNext != NULL );
	assert( aList.myLast->myNext == NULL );
	cout << " 2 " << flush;
	// append to a list containing 2 Items
	aList.append(33);
	assert( aList.getSize() == 3 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast != NULL );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 33 );
	assert( aList.myFirst->myNext->myItem == 22 );
	assert( aList.myLast->myNext == NULL );
	cout << " 3 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testDestructor() {
	cout << "Testing destructor... " << flush;
	List<double> aList;
	aList.~List();
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << " 1 " << flush;

	aList.append(11);
	aList.append(22);
	aList.append(33);
	aList.~List();
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << " 2 " << flush;
	cout << "Passed!  But double-check for memory leaks!" << endl;
}

void ListTester::testCopyConstructor() {
	cout << "Testing copy constructor... " << flush;
	// copy empty list
	List<double> list1;
	List<double> list2(list1);
	assert( list2.getSize() == 0 );
	assert( list2.myFirst == NULL );
	assert( list2.myLast == NULL );
	cout << " 1 " << flush;

	// copy nonempty list
	List<double> list3;
	list3.append(11);
	list3.append(22);
	list3.append(33);
	List<double> list4(list3);
	assert( list4.getSize() == 3 );
	assert( list4.getFirst() == 11 );
	assert( list4.getLast() == 33 );
	assert( list4.myFirst->myNext->myItem == 22 );
	assert( list4.myFirst != list3.myFirst );
	assert( list4.myLast != list3.myLast );
	cout << " 2 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testAssignment() {
	cout << "Testing assignment... " << flush;
	// empty to empty assignment
	List<double> list1;
	List<double> list2;
	list2 = list1;
	assert( list2.getSize() == 0 );
	assert( list2.myFirst == NULL );
	assert( list2.myLast == NULL );
	cout << " 1 " << flush;

	// non-empty to empty assignment
	List<double> list3;
	list3.append(11);
	list3.append(22);
	list3.append(33);
	List<double> list4;
	list4 = list3;
	assert( list4.getSize() == 3 );
	assert( list4.getFirst() == 11 );
	assert( list4.getLast() == 33 );
	assert( list4.myFirst->myNext->myItem == 22 );
      // check that nodes are distinct
	assert( list4.myFirst != list3.myFirst );
	assert( list4.myFirst->myNext != list3.myFirst->myNext );
	assert( list4.myLast != list3.myLast );
	cout << " 2 " << flush;

	// equal-sized non-empty to non-empty assignment
	List<double> list5;
	list5.append(44);
	list5.append(55);
	list5.append(66);
	list5 = list3;
	assert( list5.getSize() == 3 );
	assert( list5.getFirst() == 11 );
	assert( list5.getLast() == 33 );
	assert( list5.myFirst->myNext->myItem == 22 );
      // check that nodes are distinct
	assert( list5.myFirst != list3.myFirst );
	assert( list5.myFirst->myNext != list3.myFirst->myNext );
	assert( list5.myLast != list3.myLast );
	cout << " 3 " << flush;

	// empty to non-empty assignment
	List<double> list6;
	list6.append(44);
	list6.append(55);
	list6.append(66);
	List<double> list7;
	list6 = list7;
	assert( list6.getSize() == 0 );
	assert( list6.myFirst == NULL );
	assert( list6.myLast == NULL );
	cout << " 4 " << flush;

	// unequal-sized non-empty to non-empty assignment
	List<double> list8;
	list8.append(44);
	list8.append(55);
	list8.append(66);
	list8.append(77);
	list8 = list3;
	assert( list8.getSize() == 3 );
	assert( list8.getFirst() == 11 );
	assert( list8.getLast() == 33 );
	assert( list8.myFirst->myNext->myItem == 22 );
      // check that nodes are distinct
	assert( list8.myFirst != list3.myFirst );
	assert( list8.myFirst->myNext != list3.myFirst->myNext );
	assert( list8.myLast != list3.myLast );
	cout << " 5 " << flush;

	// assignment chaining
	List<double> list9;
	list9.append(44);
	list9.append(55);
	list9.append(66);
	list9.append(77);
	List<double> list10;
	list10 = list9 = list8;
	assert( list10.getSize() == 3 );
	assert( list10.getFirst() == 11 );
	assert( list10.getLast() == 33 );
	assert( list10.myFirst->myNext->myItem == 22 );
	cout << " 6 " << flush;

	// self-assignment (stupid, but possible)
	List<double> list11;
	list11.append(11);
	list11.append(22);
	list11.append(33);
	list11 = list11;
	assert( list11.getSize() == 3 );
	assert( list11.getFirst() == 11 );
	assert( list11.getLast() == 33 );
	assert( list11.myFirst->myNext->myItem == 22 );
	cout << " 7 " << flush;

	cout << "Passed!  But double-check for memory leaks!" << endl;
}

void ListTester::testEquality() {
	cout << "Testing operator==..." << flush;
	List<double> list0; //empty list

	List<double> list1;
	list1.append(11);
	list1.append(22);
	list1.append(33);

	List<double> list2(list1);

	List<double> list3;
	list3.append(11);
	list3.append(33);

	List<double> list4;
	list4.append(11);
	list4.append(0);
	list4.append(33);


	bool tester = list1 == list2;	//test equal lists
	assert(tester == true);
	cout << " 1 " << flush;
	tester = list1 == list0;	//test unequal lists - one is empty
	assert( tester == false);
	cout << " 2 " << flush;
	tester = list1 == list3;	//test unequal lists - different sizes, same first and last items
	assert( tester == false);
	cout << " 3 " << flush;
	tester = list1 == list4;	//test list with same size and same first and last items
	assert( tester == false);
	cout << " 4 " << flush;

	cout << "Passed!" << endl;
}

void ListTester::testInequality() {
	cout << "Testing operator!=..." << flush;
	List<double> list0; //empty list

	List<double> list1;
	list1.append(11);
	list1.append(22);
	list1.append(33);

	List<double> list2(list1);

	List<double> list3;
	list3.append(11);
	list3.append(33);

	List<double> list4;
	list4.append(11);
	list4.append(0);
	list4.append(33);


	bool tester = list1 != list2;	//test equal lists
	assert(tester == false);
	cout << " 1 " << flush;
	tester = list1 != list0;	//test unequal lists - one is empty
	assert( tester == true);
	cout << " 2 " << flush;
	tester = list1 != list3;	//test unequal lists - different sizes, same first and last items
	assert( tester == true);
	cout << " 3 " << flush;
	tester = list1 != list4;	//test list with same size and same first and last items
	assert( tester == true);
	cout << " 4 " << flush;

	cout << "Passed!" << endl;
}

void ListTester::testReadFromStream() {
	cout << "Testing readFromStream..." <<flush;
	List<double> list0;
	ifstream fin("ListTest.txt");
	assert( fin.is_open());
	list0.readFrom(fin);
	assert( list0.mySize == 3 );
	cout << " 1 " << flush;
	assert( list0.getFirst() == 11 );
	cout << " 2 " << flush;
	assert( list0.myFirst->myNext->myItem == 22 );
	cout << " 3 " << flush;
	assert( list0.getLast() == 33 );
	cout << " 4 " << flush;
	assert( list0.myLast->myNext == NULL);
	cout << " 5 " << flush;
	cout << "Passed!" << endl;
}
void ListTester::testReadFromString() {
	cout << "Testing readFrom(string)..." << flush;
	List<double> list0;
	list0.readFrom("ListTest.txt");
	cout << " 1 " << flush;
	assert( list0.myFirst->myItem == 11);
	cout << " 2 " << flush;
	assert( list0.myFirst->myNext->myItem == 22);
	cout << " 3 " << flush;
	assert (list0.getLast() == 33);
	cout << " 4 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testWritetoString() {
	cout << "Testing writeTo(string)" << flush;
	List<double> list0, list1;
	list0.append(11);
	list0.append(22);
	list0.append(33);
	list0.writeTo("ListOut.txt");
	cout << " 1 " << flush;
	ifstream fin("ListOut.txt");
	assert( fin.is_open());
	unsigned a, b, c;
	fin >> a >> b >> c;
	assert(a == 11);
	cout << " 2 " << flush;
	assert(b == 22);
	cout << " 3 " << flush;
	assert(c == 33);
	cout << " 4 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testPrepend() {
	cout << "Testing prepend()..." << flush;
	List<double> list0, list1, list2;
	list0.prepend(88);
	assert (list0.getSize() == 1);
	assert( list0.getFirst() == 88);
	assert( list0.getLast() == 88);
	cout << " 1 " << flush;

	list1.append(11);
	list1.append(22);
	list1.append(33);
	list1.prepend(88);
	assert( list1.getFirst() == 88); //prepend result
	cout << " 2 " << flush;
	assert( list1.myFirst->myNext->myItem == 11); //test node changes
	cout << " 3 " << flush;
	assert( list1.myFirst->myNext->myNext->myItem == 22);
	cout << " 4 " << flush;
	assert( list1.getLast() == 33);
	cout << " 5 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testInsert() {
	cout << "Testing insert()..." << flush;
	List<double> list0;
	list0.append(11);
	list0.append(44);
	list0.append(66);
	list0.insert(22, 1);
	list0.insert(33, 2);
	list0.insert(55, 4);
	try {
			list0.insert(99, 10);
			cerr << "insert worked with out of range index" << endl;
			exit(1);
		}
	catch (invalid_argument&) {
			cout << " 0 " << flush;
	}
	assert( list0.myFirst->myItem == 11 );
	cout << " 1 " << flush;
	assert( list0.myFirst->myNext->myItem == 22);
	cout << " 2 " << flush;
	assert( list0.myFirst->myNext->myNext->myItem == 33);
	cout << " 3 " << flush;
	assert( list0.myFirst->myNext->myNext->myNext->myItem == 44);
	cout << " 4 " << flush;
	assert( list0.myFirst->myNext->myNext->myNext->myNext->myItem == 55);
	cout << " 5 " << flush;
	assert( list0.getLast() == 66);
	cout << " 6 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testInsertAt() {
	cout << "Testing insertAfter()..." << flush;
	List<string> list0;
	list0.append("Test");
	list0.append("item");
	list0.append("!");

	list0.insertAfter("Test", "ing");
	cout << " 0a " << flush;
	list0.insertBefore("!", "insertion");
	cout << " 0b " << flush;
	assert( list0.myFirst->myItem == "Test");
	assert( list0.myFirst->myNext->myItem == "ing");
	cout << " 1 " << flush;
	assert( list0.myFirst->myNext->myNext->myItem == "item");
	cout << " 2 " << flush;
	assert( list0.myFirst->myNext->myNext->myNext->myItem == "insertion");
	cout << " 3 " << flush;
	assert( list0.myLast->myItem == "!");
	cout << " 4 " << flush;
	assert( !list0.insertAfter("Tom", "thumb"));
	cout << " 5 " << flush;
	assert( !list0.insertBefore("Mary", "Jane"));
	cout << " 6 " << flush;
	cout << "Passed!" << endl;
	cout << "Testing cout" << endl;
	cout << list0 << " " << flush;
	cout << "Passed" << endl;
}

