#ifndef ASS1_LIBRARY_H
#define ASS1_LIBRARY_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Library {

private:
	vector<string> shelf;
	string libName;
	static const int MAX = 100;
	int numBooks = 0;

	friend ostream& operator<<(ostream& Out, const Library& Lib);

public:
	explicit Library(const string& Name);

	virtual ~Library();

	bool addBook(const string& BookName);

	bool removeBook(const string& BookName);

	void listAllBooks() const;

	bool isInLibrary(const string& BookName) const;

};

#endif  // ASS1_LIBRARY_H
