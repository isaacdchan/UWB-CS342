#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

ostream &operator<<(ostream &Out, const SkipList &SkipL) {
  return Out;
}

SkipList::SNode::SNode(int Data) {
	Data = Data;
	Next = nullptr;
	Prev = nullptr;
	UpLevel = nullptr;
	DownLevel = nullptr;
}

SkipList::SkipList(int Depth) {
	FrontGuards = new SNode* [Depth];
	RearGuards = new SNode* [Depth];

	for (int i = 0; i < Depth+1; i++) {
		FrontGuards[i] =  new SNode(INT_MAX);
		RearGuards[i] = new SNode(INT_MAX);
		
		FrontGuards[i]->Next = RearGuards[i];
		RearGuards[i]->Prev = FrontGuards[i];
	}

	for (int i = 0; i < Depth i++) {
		FrontGuards[i]->UpLevel = FrontGuards[i + 1];
		FrontGuards[i+1]->DownLevel = FrontGuards[i];

		RearGuards[i]->UpLevel = RearGuards[i + 1];
		RearGuards[i + 1]->DownLevel = RearGuards[i];
	}
}

void SkipList::linkSNodes(SNode* SNode1, SNode* SNode2, string Direction) {
	if (Direction == "horizontal") {
		SNode1->Next = SNode2;
		SNode2->Prev = SNode1;
	}
	else {
		SNode1->UpLevel = SNode2;
		SNode2->DownLevel = SNode1;
	}
}



bool SkipList::isHeads() {
	return rand() % 2;
}

void SkipList::insertBetweenNext(SkipList::SNode* Curr, SkipList::SNode* newSNode) {
	SNode* nextSNode = Curr->Next;
	linkSNodes(Curr, newSNode, "horizontal");
	linkSNodes(newSNode, nextSNode, "horizontal");
}

// top level can contain nodes other than -inf and +inf
SkipList::SNode* SkipList::findLeftLinkUp(SkipList::SNode* Curr) {
	while (Curr != nullptr) {
		if (Curr->UpLevel != nullptr)
			break;
		Curr = Curr->Prev;
	}

	return Curr;
}

void SkipList::addAbove(int currLevel, SkipList::SNode* Curr) {
	if (currLevel >= Depth || isHeads())
		return;

	SNode* leftLinkUp = findLeftLinkUp(Curr);
	if (leftLinkUp == nullptr)
		return;

	SNode* topLeftSNode = leftLinkUp->UpLevel;

	SNode* CurrCopy = &SNode(Curr->Data);
	insertBetweenNext(topLeftSNode, CurrCopy);

	linkSNodes(Curr, CurrCopy, "vertical");

	addAbove(currLevel++, CurrCopy);
}

bool SkipList::add(int Data) {
	SNode* Curr = FrontGuards[0];

	while (Curr != nullptr && Data < Curr->Next->Data)
		Curr = Curr->Next;

	if (Curr->Data == Data)
		return false;

	SNode* newSNode = &SNode(Data);
	insertBetweenNext(Curr, newSNode);
	Curr = Curr->Next;
	addAbove(0, Curr);

	return true;
}

  // need to delete individual nodes
SkipList::~SkipList() {
}

bool SkipList::remove(int Data) {
	SNode* Curr = FrontGuards[0];

	while (Curr != nullptr && Data < Curr->Next->Data)
		Curr = Curr->Next;

	if (Curr->Data == Data) {
		SNode* prevSNode = Curr->Prev;
		SNode* nextSNode = Curr->Next;

		prevSNode->Next = nextSNode;
		return true;
	}

	return false;
}

bool SkipList::contains(int Data) {
  return false;
}