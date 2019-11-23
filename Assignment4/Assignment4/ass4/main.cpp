#include "skiplist.h"
#include <iostream>
#include <sstream>

using namespace std;

int TotalPassed = 0;
int TotalTests = 0;

template <typename T> string isOK(const T &got, const T &expected) {
	++TotalTests;
	if (got == expected) {
		++TotalPassed;
		return "OK: ";
	}
	cout << "\tGot\t" << got << "\n\texpected\t" << expected << endl;
	return "ERR: ";
}

void test01() {
	SkipList Skip;
	stringstream Ss;
	Ss << Skip;
	cout << isOK(Ss.str(), "LEVEL 0: -2147483648, 2147483647, \n"s)
		<< "Empty SkipList" << endl;
	Skip.add(10);
	Skip.add(30);
	Skip.add(5);
	Skip.add(25);
	Ss.str("");
	Ss << Skip;
	cout << Ss.str() << endl;
	cout << isOK(Ss.str(),
		"LEVEL 0: -2147483648, 5, 10, 25, 30, 2147483647, \n"s)
		<< "Added 10, 30, 5, 25," << endl;
}

void test02() {
  SkipList Skip(3);
  stringstream Ss;
  Ss << Skip;
  cout << isOK(Ss.str(), "LEVEL 2: -2147483648, 2147483647, \n"s +
                             "LEVEL 1: -2147483648, 2147483647, \n"s +
                             "LEVEL 0: -2147483648, 2147483647, \n"s)
       << "Empty SkipList of Depth=3" << endl;
  srand(100);
  Skip.add(10);
  Skip.add(30);
  Skip.add(5);
  Skip.add(25);
  Ss.str("");
  Ss << Skip;
  cout << isOK(Ss.str(),
               "LEVEL 2: -2147483648, 5, 25, 2147483647, \n"s +
                   "LEVEL 1: -2147483648, 5, 25, 30, 2147483647, \n"s +
                   "LEVEL 0: -2147483648, 5, 10, 25, 30, 2147483647, \n"s)
       << "SkipList of Depth=3 with 10, 30, 5, 25" << endl;
  cout << isOK(Skip.contains(10), true) << "Contains 10" << endl;
  cout << isOK(Skip.contains(30), true) << "Contains 30" << endl;
  cout << isOK(Skip.contains(71), false) << "Does not contain 71" << endl;
  Skip.add(71);
  cout << isOK(Skip.contains(71), true) << "Contains 71" << endl;
  cout << isOK(Skip.add(71), false) << "Duplicates not allowed: 71" << endl;
  cout << isOK(Skip.remove(71), true) << "Able to remove 71" << endl;
  cout << isOK(Skip.contains(71), false) << "No longer contains 71" << endl;
}


int main() {
  // NOLINTNEXTLINE
   test01();
   test02();
  // cout << "Passed: " << TotalPassed << "/" << TotalTests << endl;
  return 0;
}