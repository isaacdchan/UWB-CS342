
#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H

#include <fstream>
#include <string>

using namespace std;

class Account {
public:
	Account(int id, string Name);
	int GetId();
private:
	int id;
	string Name;
	int balances[];
};
#endif // ASS5_ACCOUNT_H
