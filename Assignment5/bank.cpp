// figure out display output ordering (string + ss<<)
// check which parameters can be const static or references

#include "bank.h"

Bank::Bank() {
	Queue = new queue<Bank::Transaction*>();
	// display errors using ss and pushback
	Errors = new vector<string>;
	Tree = new AccountTree();
};

Bank::~Bank() = default;

Bank::Transaction::Transaction(int Account, int ToAccount, string Name, char Action, int Amount) {
	this->Account = Account;
	this->ToAccount = ToAccount;
	this->Name = Name;
	this->Action = Action;
	this->Amount = Amount;

}

void Bank::ConvertTxtToQueue(const string & FileName) {
	Queue = new queue<Transaction*>();
	// display errors using ss and pushback
	Errors = new vector<string>;
	Tree = new AccountTree();

	ifstream infile(FileName);
	string line;
	for (line; getline(infile, line);) {
		ConvertStringToTransaction(line);
	}
}

void Bank::ConvertStringToTransaction(string line) {
	char Action = line[0];
	line.erase(0, 2);

	int AccountInfo = -1;
	int ToAccount = -1;
	int Amount = 0;
	string Name = "";

	if (Action == 'O') {
		int FNameEnd = line.find(' ');
		string FName = line.substr(0, FNameEnd);
		line.erase(0, FNameEnd + 1); // +1 to account for the space

		int LNameEnd = line.find(' ');
		string LName = line.substr(0, LNameEnd);
		line.erase(0, LNameEnd + 1);

		Name = FName + " " + LName;

		AccountInfo = stoi(line.substr(0, line.size()));
	}
	else if (Action == 'H')
		AccountInfo = stoi(line.substr(0, line.size()));

	else {
		int AccountEnd = line.find(' ');
		int Account = stoi(line.substr(0, AccountEnd));
		line.erase(0, AccountEnd + 1);

		if (Action == 'T') {
			int AmountEnd = line.find(' ');
			int Amount = stoi(line.substr(0, AmountEnd));
			line.erase(0, AmountEnd + 1);

			int ToAccount = stoi(line.substr(0, line.size()));
		}
		else
			int Amount = stoi(line.substr(0, line.size()));
	}
	Queue->push(new Transaction(AccountInfo, ToAccount, Name, Action, Amount));
}

void Bank::ProcessQueue() {
	while (!Queue->empty()) {
		ProcessTransaction(Queue->front());
		Queue->pop();
	}
}

void Bank::ProcessTransaction(Transaction* T) {
	cout << T->Action << endl;
	if (T->Action == 'O')
		OpenAction(T);
	else if (T->Action == 'H')
		HistoryAction(T);

	// balance history errors go here
	else
		BalanceAction(T);
}

void Bank::OpenAction(Transaction* T) {
	Account* A = new Account(T->Account, T->Name);
	bool res = Tree->Insert(A);
	cout << res << endl;
	if (!res) {
		string Error = "ERROR: Account " + to_string(A->GetId()) + " is already open. Transaction refused.";
		Errors->push_back(Error);
	}
}
void Bank::HistoryAction(Transaction* T) {
	if (T->Account < 10000) {// no Fund paramter in transaction
		Account* A;
		bool res = Tree->Retrieve(T->Account, A);
		A->Display();
	}
	else {
		int AccountId = T->Account / 10;
		Account* A;
		bool res = Tree->Retrieve(AccountId, A);

		if (!res) {
			string Error = "ERROR: Attempted to generate history for account " + to_string(A->GetId()) + ", which does not exist";
			Errors->push_back(Error);
			return;
		}

		int Fund = T->Account % 10000;
		A->DisplayFund(Fund, "long");
	}
}
//T->Account = -1!!!
void Bank::BalanceAction(Transaction* T) {
	cout << T->Account << endl;
	int Id = T->Account / 10;
	int Fund = T->Account % 10000;

	Account* A;
	bool res = Tree->Retrieve(Id, A);
	if (!res) {
		string Error = "ERROR: Attempted to adjust balance for account " + to_string(A->GetId()) + ", which does not exist";
		Errors->push_back(Error);
		return;
	}

	A->AdjustBalance(Fund, T->Action, T->Amount, T->ToAccount);

	if (T->Action == 'T') {
		// if not enough funds, end Action. Don't deposit
		if (!A->IsValidTransaction(Fund, T->Amount))
			return;

		Account* ToAccount;
		int ToId = T->ToAccount / 10;
		int ToFund = T->ToAccount % 10000;

		//check if the ToAccount is valid
		res = Tree->Retrieve(ToId, ToAccount);
		if (!res) {
			string Error = "ERROR: Could not find Account " + to_string(A->GetId()) + ". Transfer cancelled";
			Errors->push_back(Error);
			return;
		}
		// increase the balance of the ToAccount
		ToAccount->AdjustBalance(ToFund, 'D', T->Amount, -1);
	}
}

void Bank::DisplayAllBankBalances() const {
	Tree->Display();
}
