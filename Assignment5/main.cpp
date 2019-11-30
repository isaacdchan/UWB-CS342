
#include "bank.h"
#include <iostream>
#include <string>


using namespace std;

int main(int Argc, char *Argv[]) {
    Bank Bank;
	
	for (int i = 1; i < Argc; ++I) {
		cout << "The command line argument(s) was " << Argv[i] << std::endl;
		string FileName = Argv[i];
		Bank.convertTxtToQueue(FileName);
		Bank.processQueue();
		Bank.displayErrors();
	}

	//Bank.convertTxtToQueue("C:/Users/isaac/Documents/UW Bothell/CS342/Assignment5/BankTransIn.txt");
	//Bank.processQueue();
	//Bank.displayAllBankBalances();
	//Bank.displayErrors();

    cout << "Done" << endl;
    return 0;
}