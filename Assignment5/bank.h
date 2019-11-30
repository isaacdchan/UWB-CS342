#ifndef ASS5_BANK_H
#define ASS5_BANK_H

#include "accounttree.h"
#include <fstream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

class Bank {

private:
	// what each line in input file is converted to for easier processing
	struct Transaction {
		explicit Transaction(int Account, int ToAccount, string Name, char Action, int Amount);
		int Account;
		int ToAccount;
		string Name;
		char Action;
		int Amount;
	};

	// stores order of transactions to process
	queue<Transaction*>* Queue;
	// tree structure which stores accounts
	AccountTree* Tree;
	// account based errors (no account found, dupplicate accounts)
	vector<string>* Errors;

public:
	// initializes Queue, Errors, and AccountTree
	Bank();
	// deletes Queue, Tree, and Errors
	~Bank();

	// converts each line in text file to Transaction object
	// then pushes transaction to queue
	void convertTxtToQueue(const string& FileName);
	// breakds down line string to action, amount, account/fund and other info
	void convertStringToTransaction(string& Line);

	// iterate over queue, handling each transaction
	void processQueue();
	// helper function to log which transaction the bank is processing
	void logTransaction(const Transaction* const T) const;
	// diverts transaction to action handlers
	void processTransaction(const Transaction* const T);

	// opens new account and inserts into tree
	void openAction(const Transaction* const T);
	// logs whole account history or specific fund history
	void historyAction(const Transaction* const T);
	// adjusts the balance of an account
	void balanceAction(const Transaction* const T);

	// traverse accounttree, displaying each account
	void displayAllBankBalances() const;
	// lists all account based errors
	void displayErrors() const;
};

#endif // ASS5_BANK_H