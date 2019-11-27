
#include "bank.h"
#include <iostream>
#include <string>


using namespace std;

int main(int Argc, char *Argv[]) {
    Bank Bank;
  //  for(int I = 1; I < Argc; ++I) {
  //      cout << "The command line argument(s) was " << Argv[I] << std::endl;
  //      string FileName = Argv[I];
  //      Bank.ConvertTxtToQueue(FileName);
		//Bank.ProcessQueue();
  //  }
	Bank.ConvertTxtToQueue("C:/Users/isaac/Documents/UWB/CS342/Assignment5/BankTransIn.txt");
	Bank.ProcessQueue();
    cout << "Done" << endl;
    return 0;
}