// Library class demonstrating partially filled arrays
// Can add/remove books from library
// findbooks in library

#include "library.h"
#include <iostream>
#include <vector>

using namespace std

// constructor with default name
Library::Library(const string &Name) {
  
}

// destructor
Library::~Library() {
}

// true if book found in library
bool Library::isInLibrary(const string &BookName) const {
  return true;
}

// add a new book
// return true if successful, false if
// book already in library
bool Library::addBook(const string &BookName) {
  return false;
}

// remove a book
// return true if successfully removed
// false if book not in library
bool Library::removeBook(const string &BookName) {
  return false;
}

// list all books
void Library::listAllBooks() const {
}

ostream &operator<<(ostream &Out, const Library &Lib) {
  return Out;
}
