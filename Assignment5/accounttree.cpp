#include "accounttree.h"

AccountTree::AccountTree() {
	Root = nullptr;
};

// Delete all nodes in BST
AccountTree::~AccountTree() {
	this->clear();
}

// Insert new account
bool AccountTree::insert(Account* A) { 
	AccountTree::Node* NewNode = new AccountTree::Node(A);
	AccountTree::Node* Curr = Root;
	AccountTree::Node* Prev = nullptr;

	char Direction = 'L';

	if (Curr == nullptr)
		this->Root = NewNode; 

	else {
		while (Curr != nullptr) {
			Prev = Curr;
			if (A->getId() == Curr->Account->getId())
				return false;
			else if (A->getId() < Curr->Account->getId()) {
				Curr = Curr->Left;
				Direction = 'L';
			}
			else {
				Curr = Curr->Right;
				Direction = 'R';
			}
		}
		if (Direction == 'L')
			Prev->Left = NewNode;
		else
			Prev->Right = NewNode;
	}

	return true;
}

// Retrieve account
// returns true if successful AND *Account points to account
bool AccountTree::retrieve(const int& AccountId, Account*& Account) const {
	stack <Node*> s;
	s.push(this->Root);

	while ((s.size() != 0) && (s.top() != nullptr)) {
	//while (s.top() != nullptr) {

		Node* Curr = s.top();

		if ((int) Curr->Account->getId() == AccountId) {
			Account = Curr->Account; // set Account*& to point at Curr->Account???
			return true;
		}
		
		s.pop();

		if (Curr->Left != nullptr)
			s.push(Curr->Left);
		if (Curr->Right != nullptr)
			s.push(Curr->Right);
	}

	return false;
}

// Display information on all accounts
void AccountTree::display() const {
	stack <Node*> s;
	s.push(Root);

	while ((s.size() != 0) && (s.top() != nullptr)) {
		Node* Curr = s.top();
		s.pop();

		Curr->Account->display();

		if (Curr->Left != nullptr)
			s.push(Curr->Left);
		if (Curr->Right != nullptr)
			s.push(Curr->Right);
	}
}

// delete all information in AccountTree
void AccountTree::clear() {
	stack <Node*> s;
	s.push(Root);

	while (s.top() != nullptr) {
		Node* Curr = s.top();

		if (Curr->Left != nullptr)
			s.push(Curr->Left);
		if (Curr->Right != nullptr)
			s.push(Curr->Right);

		delete Curr;

		s.pop();
	}

	Root = nullptr;
}

// check if tree is empty
bool AccountTree::isEmpty() const {
	return Root == nullptr;
}