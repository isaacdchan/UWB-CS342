
#include "bank.h"
#include <iostream>
#include <string>


using namespace std;

int main(int Argc, char *Argv[]) {
    Bank Bank;
	Bank.convertTxtToQueue("C:/Users/isaac/Documents/UW Bothell/CS342/Assignment5/BankTransIn.txt");
	Bank.processQueue();
	Bank.displayAllBankBalances();
	Bank.displayErrors();
    cout << "Done" << endl;
    return 0;
}