#include "bank.h"

Bank::Bank() {
	Tree = new AccountTree();
	Queue = new queue<Bank::Transaction>();
	Errors = new vector<string>;
};

Bank::~Bank() {
	delete Tree;
	*Queue = queue<Bank::Transaction>();
	delete Queue;
	Errors->clear();
	delete Errors;
}

Bank::Transaction::Transaction(int Account, int ToAccount, string Name, char Action, int Amount) {
	this->Account = Account;
	this->ToAccount = ToAccount;
	this->Name = Name;
	this->Action = Action;
	this->Amount = Amount;
}

void Bank::convertTxtToQueue(const string & FileName) {
	ifstream infile(FileName);
	string Line;
	for (Line; getline(infile, Line);)
		convertStringToTransaction(Line);
}

void Bank::convertStringToTransaction(string& Line) {
	string RawLine = Line;
	char Action = Line[0];
	Line.erase(0, 2);

	int AccountEnd;
	int AccountInfo = -1;
	int ToAccount = -1;
	int AmountEnd;
	int Amount = 0;
	string Name = "";

	switch (Action) {
		case 'O' : {
			int FNameEnd = Line.find(' ');
			string FName = Line.substr(0, FNameEnd);
			Line.erase(0, FNameEnd + 1); // +1 to account for the space

			int LNameEnd = Line.find(' ');
			string LName = Line.substr(0, LNameEnd);
			Line.erase(0, LNameEnd + 1);

			Name = FName + " " + LName;

			AccountInfo = stoi(Line.substr(0, Line.size()));
		}
		case 'H':
			AccountInfo = stoi(Line.substr(0, Line.size()));
		default: // D, W, T
			AccountEnd = Line.find(' ');
			AccountInfo = stoi(Line.substr(0, AccountEnd));
			Line.erase(0, AccountEnd + 1);

			if (Action == 'T') {
				AmountEnd = Line.find(' ');
				Amount = stoi(Line.substr(0, AmountEnd));
				Line.erase(0, AmountEnd + 1);

				ToAccount = stoi(Line.substr(0, Line.size()));

			}
			else
				Amount = stoi(Line.substr(0, Line.size()));
	}

	Queue->push(Transaction(AccountInfo, ToAccount, Name, Action, Amount));
}

void Bank::processQueue() {
	while (!Queue->empty()) {
		Transaction currTransaction = Queue->front();
		processTransaction(currTransaction);

		Queue->pop();
	}
}

void Bank::logTransaction(const Transaction& T) const {
	cout << "Processing Transaction:" << endl;
	cout << "Action: " << T.Action << endl;
	cout << "Account1: " << T.Account << endl;
	cout << "Account2: " << T.ToAccount << endl;
	cout << "Name: " << T.Name << endl;
	cout << "Amount: " << T.Amount << endl;
	cout << "-------------" << endl;
}

void Bank::processTransaction(const Transaction& T) {
	logTransaction(T);
	if (T.Action == 'O')
		openAction(T);
	else if (T.Action == 'H')
		historyAction(T);
	else
		balanceAction(T);
}

void Bank::openAction(const Transaction& T) {
	Account* A = new Account(T.Account, T.Name);
	bool res = Tree->insert(A);
	if (!res) {
		string Error = "ERROR: Account " + to_string(T.Account) + " is already open. Transaction refused";
		// the new account is deleted if it already exists in Tree->insert(A);
		Errors->push_back(Error);
	}
}
void Bank::historyAction(const Transaction& T) {
	// asking for whole account history
	if (T.Account < 10000) {
		Account* A;
		bool res = Tree->retrieve(T.Account, A);
		A->displayAccount();
	}
	// asking for specific fund history
	else {
		int AccountId = T.Account / 10;
		Account* A;
		bool res = Tree->retrieve(AccountId, A);

		if (!res) {
			string Error = "ERROR: Attempted to generate history for account " + to_string(A->getId()) + ", which does not exist";
			Errors->push_back(Error);
			return;
		}


		int Fund = T.Account % 10;
		A->displayFund(Fund);
	}
}
//T.Account = -1!!!
// are transfers between accounts allowed?
void Bank::balanceAction(const Transaction& T) {
	int Id = T.Account / 10;
	int Fund = T.Account % 10;

	Account* A;
	bool res = Tree->retrieve(Id, A);
	if (!res) {
		string Error = "ERROR: Attempted to adjust balance for account " + to_string(A->getId()) + ", which does not exist";
		Errors->push_back(Error);
		return;
	}

	// for Transfers, will first try withdrawing funds
	A->adjustBalance(Fund, T.Action, T.Amount, T.ToAccount);

	if (T.Action == 'T') {
		// if not enough funds, end Action. Don't deposit
		if (!A->isValidTransaction(Fund, T.Action, T.Amount))
			return;

		Account* ToAccount;
		int ToId = T.ToAccount / 10;
		int ToFund = T.ToAccount % 10;

		//check if the ToAccount is valid
		res = Tree->retrieve(ToId, ToAccount);
		if (!res) {
			string Error = "ERROR: Could not find Account " + to_string(A->getId()) + ". Transfer cancelled";
			Errors->push_back(Error);
			return;
		}
		// increase the balance of the ToAccount
		ToAccount->adjustBalance(ToFund, 'D', T.Amount, -1);
	}
}

void Bank::displayAllBankBalances() const {
	Tree->display();
}

void Bank::displayErrors() const {
	stringstream ss;

	for (auto Error: *Errors)
		ss << Error << endl;

	cout << ss.str();
}
