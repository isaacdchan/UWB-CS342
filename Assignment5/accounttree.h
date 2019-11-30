
#ifndef ASS5_ACCOUNTTREE_H
#define ASS5_ACCOUNTTREE_H

#include "account.h"
#include <iostream>
#include <stack>

class AccountTree {
public:
  // Create BST
  AccountTree();
  // Delete all nodes in BST
  ~AccountTree();
  // Insert new account
  bool insert(Account* A);
  // Retrieve account
  // returns true if successful AND *Account points to account
  bool retrieve(const int& AccountId, Account*& Account) const;
  // Display information on all accounts
  void display() const;
  // delete all information in AccountTree
  void clear();
  // check if tree is empty
  bool isEmpty() const;

private:
  class Node {
  public:
    explicit Node(Account* Account)
        : Account{Account}, Right{nullptr}, Left{nullptr} {};
	~Node();
    Account* Account;
    Node* Right;
    Node* Left;
  };
  Node* Root;
};

#endif // ASS5_ACCOUNTTREE_H
