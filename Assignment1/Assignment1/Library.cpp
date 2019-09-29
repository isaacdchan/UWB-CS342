#include "Library.h"
#include <iostream>


Library::Library(const string& Name) {
	shelf.reserve(MAX);
	libName = Name;
}

Library::~Library() {
}

bool Library::isInLibrary(const string& bookName) const {
	if ((find(shelf.begin(), shelf.end(), bookName)) != shelf.end()) {
		return true;
	}
	return false;
}

bool Library::addBook(const string& bookName) {
	if (isInLibrary(bookName)) {

		return false;
	}

	if (numBooks < MAX) {
		shelf.emplace_back(bookName);
		numBooks++;
	}
	else {
		shelf[MAX-1] = bookName;
	}

	return false;
}

bool Library::removeBook(const string& bookName) {
	std::vector<string>::iterator it = std::find(shelf.begin(), shelf.end(), bookName);
		
	if (it != shelf.end()) {
		__int64 index = distance(shelf.begin(), it);
		
		string lastBook = shelf[__int64(numBooks)-1];
		shelf[index] = lastBook;
		shelf.erase(shelf.end()-1);
		numBooks--;
		
		return true;
	}
	else {
		return false;
	}
}

void Library::listAllBooks() const {
	for (int i = 0; i < numBooks; i++) {
		std::cout << shelf[i] << endl;
	}
}

ostream& operator<<(ostream& Out, const Library& Lib) {
	return Out;
};