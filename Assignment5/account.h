
#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Account {
private:
	// account holder's id
	int Id;
	// account holder's name
	string Name;
	// array listing the corresponding cover
	int* CoverFundMatch;
	// array of balances representing balance for each fund
	int* Balances;
	// vector of vectors to store history for each fund
	vector<vector<string>*>* BalanceHistories;

	// string representations of each fund for display purposes
	const string FundNames[10] = {
		"Money Market", "Prime MoneyMarket", "Long-Term Bond",
		"Short-Term Bond", "500 Index Fund", "Capital Value Fund",
		"Growth Equity Fund", "Growth Index Fund", "Value Fund",
		"Value Stock Index"
	};

public:
	// inits Account with the id and the holder's name
	Account(int Id, string Name);
	// deletes CoverFundMatch, Balances, BalanceHistories
	~Account();
	// returns account id
	int getId() const;
	// checks if fund and coverfund (if exists) has enough for withdraw
	bool isValidTransaction(int Fund, char Action, int Amount) const;
	// logs transaction in account then adjusts fund balance if valid
	void adjustBalance(int Fund, char Action, int Amount, int ToAcc);
	// adds fund transaction to BalanceHistories[Fund]
	void addRecord(int Fund, char Action, int Amount, int ToAccount, bool IsValid);
	// lists account name, id, and then balance and balance history for each fund
	void displayAccount();
	// lists each transaction for each fund. failed transactions have "(Failed)" appended
	void displayFund(int Fund);
	// lists each transaction for each fund. failed transactions have "(Failed)" appended
	void buildFundHistory(ostream& ss, int Fund);
};
#endif // ASS5_ACCOUNT_H
