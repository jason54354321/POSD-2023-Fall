#pragma once

#include "dfs_iterator.h"
#include "iterator.h"
#include "node.h"
#include <iostream>
#include <list>
#include <sys/stat.h>
#include <vector>

using namespace std;

class Folder : public Node {
private:
  list<Node *> _nodes;
  vector<Iterator *> _iterators;

  void validateSystemPath(string path) {
    struct stat sb;

    const char *pathcc = path.c_str();
    if (stat(pathcc, &sb) == -1) {
      cout << "Error when File new" << endl;
      throw "validation fail, no such file exist";
    }
  }

  void disableExistIterator() {
    for (Iterator *it : _iterators) {
      it->setEnable(false);
    }
    _iterators.clear();
  }

protected:
  void removeChild(Node *target) override {
    _nodes.remove(target);
  }

public:
  class FolderIterator : public Iterator {
  public:
    FolderIterator(Folder *composite);
    ~FolderIterator() override {
    }
    void first() override;
    Node *currentItem() const override;
    void next() override;
    bool isDone() const override;

  private:
    Folder *const _host;
    std::list<Node *>::iterator _current;
  };
  Folder(string path) : Node(path) {
    validateSystemPath(path);
  }

  void add(Node *node) override {
    disableExistIterator();

    if (node->path() != this->path() + "/" + node->name()) {
      throw string("Incorrect path of node: " + node->path());
    }
    _nodes.push_back(node);
    node->parent(this);
  }

  Node *getChildByName(const char *name) const override {
    for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
      if ((*it)->name() == name) {
        return *it;
      }
    }
    return nullptr;
  }

  int numberOfFiles() const override {
    int num = 0;
    if (_nodes.size() == 0) {
      return 0;
    }
    for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
      num += (*it)->numberOfFiles();
    }
    return num;
  }

  Iterator *createIterator() override {
    Iterator *it = new FolderIterator(this);
    _iterators.push_back(it);

    return it;
  }

  Iterator *dfsIterator() override {
    return new DfsIterator(this);
  }

  Node *find(string path) override {
    if (this->path() == path) {
      return this;
    }

    size_t index = path.find(this->path());

    if (string::npos == index) {
      return nullptr;
    }

    for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
      Node *result = (*it)->find(path);
      if (result) {
        return result;
      }
    }
    return nullptr;
  }

  std::list<string> findByName(string name) override {
    std::list<string> pathList;
    if (this->name() == name) {
      pathList.push_back(this->path());
    }

    for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
      std::list<string> paths = (*it)->findByName(name);
      for (auto i = paths.begin(); i != paths.end(); i++) {
        pathList.push_back(*i);
      }
    }

    return pathList;
  }

  void remove(string path) override {
    Node *target = find(path);
    if (target) {
      target->parent()->removeChild(target);
    }
  }

  void accept(Visitor *visitor) override {
    visitor->visitFolder(this);
  }
};
