#include "iterator.h"
#if !defined(NODE_H)
#define NODE_H

#include <string>

using namespace std;

class Node {
public:
  virtual string name() const = 0;

  virtual string path() const = 0;

  void add(Node *node);

  void remove(string path);

  Node *getChildByName(const char *name) const;

  int numberOfFiles() const;

  virtual Iterator *createIterator() = 0;

  /* Iterator * createIterator(); */
};

#endif // NODE_H
