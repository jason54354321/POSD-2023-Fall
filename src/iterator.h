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
  void first();
  Node *currentItem() const;
  void next();
  bool isDone() const;
};

// Is a stateful class
class FolderIterator : public Iterator {
private:
  Folder *_folder;
  std::vector<Node *>::iterator _it;

public:
  FolderIterator(Folder *folder);
  void first();
  Node *currentItem() const;
  void next();
  bool isDone() const;
};

#endif // ITERATOR_H
