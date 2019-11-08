#ifndef ASS4_SKIP_LIST_SKIPLIST_H
#define ASS4_SKIP_LIST_SKIPLIST_H

#include <iostream>

using namespace std;

class SkipList {
  // display with level
  friend ostream &operator<<(ostream &Out, const SkipList &SkipL);

private:
  // private SNode
  // defined in .cpp as SkipList::SNode::SNode(int Data) ...
  struct SNode {
    explicit SNode(int Data);
    int Data;
    // link to Next SNode
    SNode* Next;
    // link to Prev SNode
    SNode* Prev;
    // link to up one level
    SNode* UpLevel;
    // link to down one level
    SNode* DownLevel;
  };

  using Snode = struct Snode;

  // Depth of SkipList
  int Depth;

  // array of Depth SNode* objects as FrontGuards linking levels
  SNode** FrontGuards;

  // array of Depth SNode* objects as RearGuards linking levels
  SNode** RearGuards;

  // given a SNode, place it before the given NextNode
  void addBefore(SNode* NewNode, SNode* NextNode);

public:
  // default SkipList has Depth of 1, just one doubly-linked list
  explicit SkipList(int Depth = 1);

  // destructor
  virtual ~SkipList();

  void insertBetweenNext(SNode* Curr, SNode* newSNode);
  bool isHeads();

  // returns most recent previous node with an UpLevel ptr
  SNode* findPrevLinkUp(SNode* Curr);

  void linkSNodes(SNode* SNode1, SNode* SNode2, string Direction)

  void addAbove(int Data);
  // return true if successfully added, no duplicates
  bool add(int Data);

  // return true if successfully removed
  bool remove(int Data);

  // return true if found in SkipList
  bool contains(int Data);
};

#endif // ASS4_SKIP_LIST_SKIPLIST_H
