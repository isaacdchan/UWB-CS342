#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

// displays the level and the nodes at each level 
ostream &operator<<(ostream &Out, const SkipList &Skip) {
	// iterate from the top down
	for (int i = Skip.Depth-1; i >= 0; i--) {
		SkipList::SNode* Curr = Skip.FrontGuards[i];
		Out << "LEVEL " << i << ": ";
		// traverse right, printing node data along the way
		while(Curr != nullptr) {
			Out << Curr->Data << ", ";
			Curr = Curr->Right;
		}
		Out << endl;
	}
  	return Out;
}

// constructor for SNode. R, L, U, D pointers set as nullptr
SkipList::SNode::SNode(int Data) {
	this->Data = Data;
	Right = nullptr;
	Left = nullptr;
	Up = nullptr;
	Down = nullptr;
}

// default SkipList has Depth of 1, just one doubly-linked list
SkipList::SkipList(int Depth) {
	this->Depth = Depth; 
	FrontGuards = new SNode* [Depth];
	RearGuards = new SNode* [Depth];

	// creates front and rear guard nodes for each level and links them
	for (int i = 0; i < Depth; i++) {
		FrontGuards[i] = new SNode(INT_MIN);
		RearGuards[i] = new SNode(INT_MAX);
		
		linkSNodes(FrontGuards[i], RearGuards[i], "h");
	}

	// links all adjacent front guards. links all adjacent rear guards
	for (int i = 0; i < Depth-1; i++) {
		linkSNodes(FrontGuards[i], FrontGuards[i + 1], "v");
		linkSNodes(RearGuards[i], RearGuards[i + 1], "v");
	}
}

// destructor. deletes every node and then the front and read guard array
SkipList::~SkipList() {
	// start at the bottom
	SNode* Curr = FrontGuards[0];

	// deletes vertically, then traverses horizontally
	while (Curr != nullptr) {
		SNode* rightSNode = Curr->Right;
		while (Curr != nullptr) {
			SNode* upSNode = Curr->Up;
			SNode* Prev = Curr;
			Curr = upSNode;
			delete Prev;
		}
		Curr = rightSNode;
	}

	delete[] FrontGuards;
	delete[] RearGuards;
}

// returns boolean value indiciating heads or tails
bool SkipList::isHeads() {
	return rand() % 2 == 1;
}

// links two nodes either horizontally or vertically
void SkipList::linkSNodes(SNode* SNode1, SNode* SNode2, string Direction) {
	if (Direction == "h") {
		SNode1->Right = SNode2;
		SNode2->Left = SNode1;
	}
	else {
		SNode1->Up = SNode2;
		SNode2->Down = SNode1;
	}
}

// insert newSNode between Curr and Curr->Right
// TOO FUCKING LONG
void SkipList::insertBetweenRight(SkipList::SNode* Curr, SkipList::SNode* newSNode) {
	SNode* nextSNode = Curr->Right;
	linkSNodes(Curr, newSNode, "h");
	linkSNodes(newSNode, nextSNode, "h");
}

// returns the closest Left node with an Up ptr that isn't nullptr
SkipList::SNode* SkipList::findLeftLinkUp(SkipList::SNode* Curr) {
	while (Curr != nullptr) {
		if (Curr->Up != nullptr)
			break;
		Curr = Curr->Left;
	}

	return Curr;
}

// checks if should add to above level based on coin flip
// recursively calls with incremented level until currLevel >= Depth
void SkipList::addAbove(int currLevel, SkipList::SNode* Curr) {
	if (currLevel >= Depth || isHeads())
		return;

	SNode* leftLinkUp = findLeftLinkUp(Curr);
	if (leftLinkUp == nullptr)
		return;

	SNode* topLeft = leftLinkUp->Up;

	auto* CurrCopy = new SNode(Curr->Data);
	insertBetweenRight(topLeft, CurrCopy);

	linkSNodes(Curr, CurrCopy, "v");

	addAbove(currLevel++, CurrCopy);
}

// return true if successfully added, false if Data already exists
bool SkipList::add(int Data) {
	SNode* Curr = FrontGuards[Depth - 1];

	while (true) {
		if (Data >= Curr->Right->Data)
			Curr = Curr->Right;
		else
			if (Curr->Down != nullptr)
				Curr = Curr->Down;
			else
				break;
	}

	if (Curr->Data == Data)
		return false;

	auto* newSNode = new SNode(Data);
	insertBetweenRight(Curr, newSNode);
	Curr = Curr->Right;

	addAbove(0, Curr);

	return true;
}

// return true if successfully removed
bool SkipList::remove(int Data) {
	//prevents removal of front and rear guards
	if (Data >= INT_MAX || Data <= INT_MIN)
		return false;

	SNode* Curr = FrontGuards[Depth - 1];

	// finds the highest most occurence of Data
	while (true) {
		if (Curr->Data == Data)
			break;
		if (Data >= Curr->Right->Data)
			Curr = Curr->Right;
		else
			if (Curr->Down != nullptr)
				Curr = Curr->Down;
			else
				return false;
	}

	// traverses down connecting L and R nodes to each other
	// then deleting self
	while (Curr != nullptr) {
		SNode* Prev = Curr;
		SNode* downSNode = Curr->Down;
		linkSNodes(Curr->Left, Curr->Right, "h");
		Curr = downSNode;
		delete Prev;
	}

	return true;
}

// return true if found in SkipList
bool SkipList::contains(int Data) {
	SNode* Curr = FrontGuards[Depth-1];

	while (true) {
		if (Curr->Data == Data)
			return true;
		if (Data >= Curr->Right->Data)
			Curr = Curr->Right;
		else
			if (Curr->Down != nullptr)
				Curr = Curr->Down;
			else
				break;
	}

	return false;
}