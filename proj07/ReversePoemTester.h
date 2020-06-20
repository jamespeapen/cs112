/* Tester for ReversePoem class
 * Student Name: James Eapen
 * Date: 3/27/2019
 */

#ifndef REVERSEPOEMTESTER_H_
#define REVERSEPOEMTESTER_H_
#include "ReversePoem.h"

class ReversePoemTester {
public:
	ReversePoemTester();
	void runTests();
	void testConstructor();
	void testGetTitleGetAuthor();
	void testGetAuthor();
	void testGetBody();
	void testGetBodyReversed();
};

#endif /* REVERSEPOEMTESTER_H_ */
