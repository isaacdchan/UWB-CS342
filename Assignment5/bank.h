
#ifndef ASS5_BANK_H
#define ASS5_BANK_H

#include "accounttree.h"
#include <queue>
#include <fstream>
#include <string>

using namespace std;

class Bank {

private:
	struct Transaction {
		explicit Transaction(int id1, int id2, string Name, char Action, int Amount);
		int Account1;
		int Account2;
		string Name;
		char Action;
		int Amount;
	};

	queue<Transaction> Queue;
	AccountTree Tree;

public:
	Bank();
	~Bank();
	void convertTxtToQueue(const string& FileName);
	Transaction ConvertStringToTransaction(string line);

	bool processTransaction(Transaction T);
	void processTransactions();
	void displayAllBankBalances() const;
};



#endif // ASS5_BANK_H
