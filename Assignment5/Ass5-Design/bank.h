#ifndef ASS5_BANK_H
#define ASS5_BANK_H

#include "accounttree.h"
#include <queue>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Bank {

private:
	struct Transaction {
		explicit Transaction(int Account, int ToAccount, string Name, char Action, int Amount);
		int Account;
		int ToAccount;
		string Name;
		char Action;
		int Amount;
	};

	queue<Transaction*>* Queue;
	AccountTree* Tree;
	vector<string>* Errors;

public:
	Bank();
	~Bank();

	void ConvertTxtToQueue(const string& FileName);
	void ConvertStringToTransaction(string line);

	void ProcessQueue();
	void ProcessTransaction(Transaction* T);

	void OpenAction(Transaction* T);
	void HistoryAction(Transaction* T);
	void BalanceAction(Transaction* T);

	void DisplayAllBankBalances() const;
};



#endif // ASS5_BANK_H
