#ifndef ASS4_SKIP_LIST_SKIPLIST_H
#define ASS4_SKIP_LIST_SKIPLIST_H

#include <iostream>

using namespace std;

class SkipList {
  // displays the level and the nodes at each level 
  friend ostream &operator<<(ostream &Out, const SkipList &Skip);

private:
  // private SNode
  // defined in .cpp as SkipList::SNode::SNode(int Data) ...
  struct SNode {
	// constructor for SNode. R, L, U, D pointers set as nullptr
    explicit SNode(int Data);
    int Data;
    // link to Right SNode
    SNode* Right;
    // link to Left SNode
    SNode* Left;
    // link to up one level
    SNode* Up;
    // link to down one level
    SNode* Down;
  };

  using Snode = struct Snode;

  // Depth of SkipList
  int Depth;

  // array of Depth SNode* objects as FrontGuards linking levels
  SNode** FrontGuards;

  // array of Depth SNode* objects as RearGuards linking levels
  SNode** RearGuards;

public:
  // default SkipList has Depth of 1, just one doubly-linked list
  explicit SkipList(int Depth=1);

  // destructor. deletes every node and then the front and read guard array
  virtual ~SkipList();

  // returns boolean value indiciating heads or tails
  bool isHeads();

  // links two nodes either horizontally or vertically
  void linkSNodes(SNode* SNode1, SNode* SNode2, string Direction);

  // insert newSNode between Curr and Curr->Right
  void insertBetweenRight(SNode* Curr, SNode* newSNode);

  // returns the closest Left node with an Up ptr that isn't nullptr
  SNode* findLeftLinkUp(SNode* Curr);

  // checks if should add to above level based on coin flip
  // recursively calls with incremented level until currLevel >= Depth
  void addAbove(int currLevel, SNode* Curr);

  // return true if successfully added, false if Data already exists
  bool add(int Data);

  // return true if successfully removed
  bool remove(int Data);

  // return true if found in SkipList
  bool contains(int Data);
};

#endif // ASS4_SKIP_LIST_SKIPLIST_H
