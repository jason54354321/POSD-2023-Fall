#if !defined(ITERATOR_H)
#define ITERATOR_H

#include <list>
#include <vector>

#pragma once

class Node;
class Folder;

class Iterator {
public:
  ~Iterator();
  virtual void first() = 0;
  virtual Node *currentItem() const = 0;
  virtual void next() = 0;
  virtual bool isDone() const = 0;
};

// Is a stateful class
class FolderIterator : public Iterator {
private:
  Folder *_folder;
  std::vector<Node *>::iterator _it;

public:
  FolderIterator(Folder *folder);
  void first() override;
  Node *currentItem() const override;
  void next() override;
  bool isDone() const override;
};

#endif // ITERATOR_H
