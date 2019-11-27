#include "account.h"
#include <string>

Account::Account(int Id, string Name) {
	this->Id = Id;
	this->Name = Name;
	CoverFundMatch = new int[4];
	CoverFundMatch[0] = 1;
	CoverFundMatch[1] = 0;
	CoverFundMatch[2] = 3;
	CoverFundMatch[3] = 2;

	Balances = new int [10];
	BalanceHistories = new vector<vector<string>*>;

	for (int i = 0; i < 10; i++)
		BalanceHistories->push_back(new vector<string>);
}

int Account::GetId() {
	return this->Id;
}

bool Account::IsValidTransaction(int Fund, int Amount) {
	if (Balances[Fund] - Amount > 0)
		return true;

	// adjust and compensate balances here?
	if (Fund == 0 || Fund == 1) {
		if (Balances[0] + Balances[1] > Amount)
			return true;
	}
	if (Fund == 2 || Fund == 3) {
		if (Balances[2] + Balances[3] > Amount)
			return true;
	}
	return false;
}


void Account::AdjustBalance(int Fund, char Action, int Amount, int ToAccount) {
	bool IsValid = IsValidTransaction(Fund, Amount);

	AddRecord(Fund, Action, Amount, ToAccount, IsValid);

	if (!IsValid)
		return;


	else {
		int Remainder = Balances[Fund] - Amount;
		if (Remainder >= 0)
			Balances[Fund] -= Amount;
		else {
			int CoverFund = CoverFundMatch[Fund];
			Balances[Fund] = 0;
			Balances[CoverFund] -= Remainder;

			int IdAndFund = (this->Id) * 10 + Fund;

			// add a transfer record from the cover fund to the current fund
			AddRecord(CoverFund, 'T', Remainder, IdAndFund, true);
		}
	}
}

void Account::AddRecord(int Fund, char Action, int Amount, int ToAccount, bool IsValid) {
	string Record = Action + " $" + to_string(Amount);

	if (ToAccount != -1)
		Record += " " + ToAccount;

	if (!IsValid)
		Record += "(Failed)";

	vector<string>* BalanceHistory = (*BalanceHistories)[Fund];
	BalanceHistory->push_back(Record);
}

void Account::Display() {
	stringstream ss;

	ss << "Displaying Transaction History for " << Name << " by fund." << endl;
	
	for (int i = 0; i < 10; i++)
		DisplayFund(i, "short");
}

void Account::DisplayFund(int Fund, string Format) {
	stringstream ss;

	vector<string>* BalanceHistory = (*BalanceHistories)[Fund];

	if (Format == "short")
		ss << FundNames[Fund] << ": $";
	else if (Format == "long")
		ss << "Displaying Transaction History for " << Name << "'s" << FundNames[Fund] << "Fund:";

	ss << Balances[Fund] << endl;

	for (int j = 0; j < (int) BalanceHistory->size(); j++)
		ss << "\t" << (*BalanceHistory)[j] << endl;
}
