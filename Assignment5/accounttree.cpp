#include "accounttree.h"

AccountTree::AccountTree() = default;

// Delete all nodes in BST
AccountTree::~AccountTree() = default;

// Insert new account
bool AccountTree::Insert(Account* A) { 
	AccountTree::Node* NewNode = new AccountTree::Node(A);
					
	AccountTree::Node* Curr = Root;
	AccountTree::Node* Prev = nullptr;

	if (Curr == nullptr)
		this->Root = NewNode;

	else {
		while (Curr != nullptr) {
			Prev = Curr;
			if (A->GetId() == Curr->Account->GetId())
				return false;
			else if (A->GetId() < Curr->Account->GetId())
				Curr = Curr->Left;
			else
				Curr = Curr->Right;
		}

		Prev = NewNode; // set curr pointer to point at newNode???
	}

	return true;
}

// Retrieve account
// returns true if successful AND *Account points to account
bool AccountTree::Retrieve(const int& AccountId, Account*& Account) const {
	stack <Node*> s;
	s.push(this->Root);

	while (s.top() != nullptr) {
		Node* Curr = s.top();

		cout << (int)AccountId << endl;
		cout << (int)Curr->Account->GetId() << endl;

		if ((int) Curr->Account->GetId() == AccountId) {
			Account = Curr->Account; // set Account*& to point at Curr->Account???
			return true;
		}
		if (Curr->Left != nullptr)
			s.push(Curr->Left);
		if (Curr->Right != nullptr)
			s.push(Curr->Right);

		s.pop();
	}

	return false;
}

// Display information on all accounts
void AccountTree::Display() const {
	stack <Node*> s;
	s.push(Root);

	while (s.top() != nullptr) {
		Node* Curr = s.top();
		
		Curr->Account->Display();

		if (Curr->Left != nullptr)
			s.push(Curr->Left);
		if (Curr->Right != nullptr)
			s.push(Curr->Right);

		s.pop();
	}
}

// delete all information in AccountTree
void AccountTree::Clear() {
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
}

// check if tree is empty
bool AccountTree::isEmpty() const {
	return Root == nullptr;
}