
#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Account {
public:
	Account(int id, string Name);
	int GetId();
	bool IsValidTransaction(int Fund, int Amount);
	void AdjustBalance(int Fund, char Action, int Amount, int ToAcc);
	void AddRecord(int Fund, char Action, int Amount, int ToAccount, bool IsValid);
	void Display();
	void DisplayFund(int Fund, string Format);

private:
	int Id;
	string Name;
	int* CoverFundMatch;
	int* Balances;
	vector<vector<string>*>* BalanceHistories;

	string FundNames[10] = {
		"Money Market", "Prime MoneyMarket", "Long-Term Bond",
		"Short-Term Bond", "500 Index Fund", "Capital Value Fund",
		"Growth Equity Fund", "Growth Index Fund", "Value Fund",
		"Value Stock Index"
	};
};
#endif // ASS5_ACCOUNT_H
