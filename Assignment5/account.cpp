#include "account.h"
#include <string>

Account::Account(int id, string Name) {
	id = id;
	Name = Name;
}

int Account::GetId() {
	return id;
}