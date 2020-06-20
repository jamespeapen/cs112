/* ListTester.h declares the test-class for class List.
 * Joel Adams, for CS 112 at Calvin College.
 */

#ifndef LISTTESTER_H_
#define LISTTESTER_H_

class ListTester {
public:
	void runTests();
	void testDefaultConstructor();
	void testNodeDefaultConstructor();
	void testNodeExplicitConstructor();
	void testgetIndex();
	void testAppend();
	void testDestructor();
	void testCopyConstructor();
	void testAssignment();
	void testEquality();
	void testInequality();
	void testReadFromStream();
	void testReadFromString();
	void testWritetoString();
	void testPrepend();
	void testInsert();
	void testInsertAt();
};

#endif /*LISTTESTER_H_*/
