
#include "bank.h"
#include <iostream>
#include <string>


using namespace std;

int main(int Argc, char *Argv[]) {
    Bank Bank;
	
	//for (int I = 1; I < Argc; ++I) {
	//	cout << "The command line argument(s) was " << Argv[I] << std::endl;
	//	string FileName = Argv[I];
	//	Bank.convertTxtToQueue(FileName);
	//	Bank.processQueue();
	//	Bank.displayErrors();
	//}

	Bank.convertTxtToQueue("C:/Users/isaac/Documents/UW Bothell/CS342/Assignment5/BankTransIn.txt");
	Bank.processQueue();
	Bank.displayAllBankBalances();
	Bank.displayErrors();

    cout << "Done" << endl;
    return 0;
}