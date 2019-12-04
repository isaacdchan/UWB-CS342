
#include "bank.h"
#include <iostream>
#include <string>


using namespace std;

int main(int Argc, char *Argv[]) {
    Bank Bank;
	
	//for (int i = 1; i < Argc; ++i) {
	//	cout << "The command line argument(s) was " << Argv[i] << std::endl;
	//	string FileName = Argv[i];
	//	Bank.convertTxtToQueue(FileName);
	//	Bank.processQueue();
	//	Bank.displayErrors();
	//}

	string FileName = "BankTransIn.txt";
	Bank.convertTxtToQueue(FileName);
	Bank.processQueue();
	Bank.displayAllBankBalances();
	Bank.displayErrors();

    cout << "Done" << endl;
    return 0;
}