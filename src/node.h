#if !defined(NODE_H)
#define NODE_H

#include <string>

using namespace std;

class Iterator;

class Node {
public:
  virtual ~Node() {
  }
  virtual string name() const = 0;

  virtual string path() const = 0;

  virtual void add(Node *node){};

  virtual void remove(string path){};

  virtual Node *getChildByName(const char *name) const {
    return nullptr;
  };

  virtual Node *find(string path) = 0;

  virtual int numberOfFiles() const {
    return 0;
  };

  virtual Iterator *createIterator() = 0;

  /* Iterator * createIterator(); */
};

#endif // NODE_H
