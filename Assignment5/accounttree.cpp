#include "accounttree.h"
// empty

AccountTree::AccountTree(): Root(nullptr) {
}

// Delete all nodes in BST
AccountTree::~AccountTree() = default;

// Insert new account
bool AccountTree::insert(Account* AccountP) { 
	AccountTree::Node* NewNode = new AccountTree::Node(AccountP);
	
	AccountTree::Node* curr = Root;
	while (curr != nullptr) {
		if (AccountP->GetId() == curr->Account->GetId()) {}

		else if (AccountP->GetId() < curr->Account->GetId()) {
			if (curr->Left == nullptr) {

			}
		}

		else {
			if (curr->Right == nullptr) {

			}
		}
	}

	curr = NewNode;
}

// Retrieve account
// returns true if successful AND *Account points to account
bool AccountTree::retrieve(const int &AccountNumber, Account *&Account) const {
  return true;
}

// Display information on all accounts
void AccountTree::display() const {}

// delete all information in AccountTree
void AccountTree::clear() {}

// check if tree is empty
bool AccountTree::isEmpty() const {
  return true;
}