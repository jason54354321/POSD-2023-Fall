#include "folder.h"
#include "iterator.h"
#include "node.h"
#include <queue>
#include <stack>
#include <vector>

#if !defined(DFS_ITERATOR_H)
#define DFS_ITERATOR_H

using namespace std;

class DfsIterator : public Iterator {
private:
  Node *_folder;
  vector<Node *> _vec;
  int currentIndex = 0;

  void dfsHelper(Node *folder);

public:
  DfsIterator(Node *folder);

  void first() override;

  Node *currentItem() const override;

  void next() override;

  bool isDone() const override;
};

class BfsIterator : public Iterator {
private:
  Node *_folder;
  vector<Node *> _vec;
  queue<Node *> _q;
  int currentIndex = 0;
  void bfsHelper();

public:
  BfsIterator(Node *folder);

  void first() override;

  Node *currentItem() const override;

  void next() override;

  bool isDone() const override;
};

#endif // DFS_ITERATOR_H
