#include "bank.h"

Bank::Bank() = default;
Bank::~Bank() = default;

Bank::Transaction::Transaction(int Account1, int Account2, string Name, char Action, int Amount) {
	Account1 = Account1;
	Account2 = Account2;
	Name = Name;
	Action = Action;
	Amount = Amount;
}

void Bank::convertTxtToQueue(const string & FileName) {
	queue<Bank::Transaction> Queue = queue<Bank::Transaction>();

	ifstream TransIn;
	TransIn.open(FileName);

	string line;

	while (!TransIn.eof()) {
		TransIn >> line;
		Queue.push(ConvertStringToTransaction(line));
	}
}

Bank::Transaction Bank::ConvertStringToTransaction(string line) {
	char Action = line[0];
	line.erase(0, 2);

	int Account1, Account2 = -1;
	int Amount = 0;
	string Name = "";
	char Action = ' ';

	// open account only requries 1)Account1, 2)Name
	if (Action == 'O') {
		int FNEnd = line.find(' ') + 1;
		string FN = line.substr(0, FNEnd);
		line.erase(0, FNEnd);

		int LNEnd = line.find(' ') + 1;
		string LN = line.substr(0, LNEnd);
		line.erase(0, LNEnd);

		Name = FN + " " + LN;
		Account1 = stoi(line.substr(0, line.size));
	}
	// history only requires Account1
	else if (Action == 'H') {
		Account1 = stoi(line.substr(0, line.size));
	}
	// transfer requires 1)Account1, 2)Amount, 3)Account2, 
	else if (Action == 'T') {
		int account1End = line.find(' ') + 1;
		int Account1 = stoi(line.substr(0, account1End));
		int amountEnd = line.find(' ') + 1;
		int Amount = stoi(line.substr(0, amountEnd));
		int Account2 = stoi(line.substr(0, line.size));
	}
	// withdraw and deposit require 1)Account1 2)Amount
	else {
		int account1End = line.find(' ') + 1;
		int Account1 = stoi(line.substr(0, account1End));

		line.erase(0, account1End);
		int Amount = stoi(line.substr(0, line.size));
	}
	
	return Bank::Transaction(Account1, Account2, Name, Action, Amount);

}


void Bank::processTransactions() {
	AccountTree Tree = AccountTree();

	while (!Queue.empty) {
		bool res = processTransaction(Queue.front());



		Queue.pop();
	}

	//Account1 = AccountFund / 10;
	//int Fund = AccountFund % 10;
	//Account newAccount = Account(Account, FN, LN);
	//AccTree.insert(newAccount);
}

bool Bank::processTransaction(Bank::Transaction T) {
	if (T.Action == 'O') {
		Account A = Account(T.Account1, T.Name);
		Tree.insert(A)
	}
	else if (T.Action == 'H') {

	}
	else if (T.Action == 'T') {

	}
	else {

	}

	return true;
}
void Bank::displayAllBankBalances() const {}