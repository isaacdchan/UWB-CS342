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
	for (int i = 0; i < 10; i++)
		Balances[i] = 0;

	BalanceHistories = new vector<vector<string>*>;
	for (int i = 0; i < 10; i++)
		BalanceHistories->push_back(new vector<string>);
}

Account::~Account() {
	delete[] CoverFundMatch;
	delete[] Balances;
	delete[] BalanceHistories;
}

int Account::getId() const {
	return this->Id;
}

bool Account::isValidTransaction(int Fund, char Action, int Amount) const {
	// all deposits are valid
	if (Action == 'D')
		return true;
	// if the fund by itself has enough to cover the W or T return valid
	if (Balances[Fund] - Amount > 0)
		return true;

	// if a cover fund exists
	// and Balances[Fund] + Balances[CoverFund] > amount, return valid
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


void Account::adjustBalance(int Fund, char Action, int Amount, int ToAccount) {
	bool IsValid = isValidTransaction(Fund, Action, Amount);

	addRecord(Fund, Action, Amount, ToAccount, IsValid);

	if (!IsValid)
		return;

	if (Action == 'D')
		Balances[Fund] += Amount;
	else {
		int Remainder = Balances[Fund] - Amount;
		Balances[Fund] -= Amount;

		// if (Remainder < 0) AND (no cover fund OR cover fund cannot cover)
			// !IsValid would filter
		// check if this is a transaction that requires transfers compensated
		if (Remainder < 0) {
			Balances[Fund] = 0;
			int CoverFund = CoverFundMatch[Fund];
			Balances[CoverFund] -= Remainder;

			int IdAndFund = (this->Id) * 10 + Fund;

			// add a transfer record from the cover fund to the current fund
			addRecord(CoverFund, 'T', abs(Remainder), IdAndFund, true);
		}
	}

}

void Account::addRecord(int Fund, char Action, int Amount, int ToAccount, bool IsValid) {
	string Record = "";
	Record += Action;
	Record += " $" + to_string(Amount);

	if (ToAccount != -1)
		Record += " " + to_string(ToAccount);

	// append(Failed) if not valid
	if (!IsValid)
		Record += " (Failed)";

	vector<string>* BalanceHistory = (*BalanceHistories)[Fund];
	BalanceHistory->push_back(Record);
}

void Account::displayAccount() {
	stringstream ss;

	ss << "Displaying Transaction History for " << Name << " (ID: " << Id << ") by Fund" << endl;
	
	for (int i = 0; i < 10; i++)
		buildFundHistory(ss, i);

	cout << ss.str();
}

void Account::displayFund(int Fund) {
	stringstream ss;
	ss << "Displaying Transaction History for " << Name << "'s ";

	buildFundHistory(ss, Fund);
	cout << ss.str();
}

void Account::buildFundHistory(ostream& ss, int Fund) {
	vector<string>* BalanceHistory = (*BalanceHistories)[Fund];

	ss << FundNames[Fund] << ": $" << Balances[Fund] << endl;

	for (int j = 0; j < (int)BalanceHistory->size(); j++)
		ss << "\t" << (*BalanceHistory)[j] << endl;
}
