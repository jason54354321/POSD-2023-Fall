#if !defined(DFS_ITERATOR_H)
#define DFS_ITERATOR_H

#include "iterator.h"

using namespace std;

class DfsIterator : public Iterator {
private:
  Node *_folder;

public:
  DfsIterator(Node *folder) : _folder(folder){};

  void first() override;

  Node *currentItem() const override;

  void next() override;

  bool isDone() const override;
};

class BfsIterator : public Iterator {
private:
  Node *_folder;

public:
  BfsIterator(Node *folder) : _folder(folder){};

  void first() override;

  Node *currentItem() const override;

  void next() override;

  bool isDone() const override;
};

#endif // DFS_ITERATOR_H
