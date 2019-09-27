#include <iostream>
#include <cassert>
#include "Library.h"

using namespace std;

void Test1() {
	Library libs("UWB");
	libs.AddBook("Don Quixote");
	libs.AddBook("In Search of Lost Time");
	libs.AddBook("Ulysses");
	libs.AddBook("The Odyssey");
	libs.ListAllBooks();
	bool result = libs.IsInLibrary("The Odyssey");
	assert(result);
	result = libs.AddBook("The Odyssey");
	assert(!result);
	result = libs.RemoveBook("The Odyssey");
	assert(result);
	result = libs.IsInLibrary("The Odyssey");
	assert(!result);
	result = libs.RemoveBook("The Odyssey");
	assert(!result);
}
void TestAll() {
	Test1();
	cout << "Done!" << endl;
}
int main() {
	TestAll();
	return 0;
}