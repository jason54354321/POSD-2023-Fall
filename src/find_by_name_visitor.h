#pragma once

#include "./file.h"
#include "./folder.h"
#include "./visitor.h"
#include "iterator.h"
#include "list"
#include "string"

class FindByNameVisitor : public Visitor {
private:
  string _name;
  list<string> _pathList;

public:
  FindByNameVisitor(string name) : _name(name) {
  }

  void visitFile(File *file) override {
    if (file->name() == _name) {
      _pathList.push_back(file->path());
    }
  }

  void visitFolder(Folder *folder) override {
    Iterator *it = folder->createIterator();
    for (it->first(); !it->isDone(); it->next()) {
      Node *node = it->currentItem();
      node->accept(this);
    }
  }

  list<string> getPaths() {
    return _pathList;
  }
};
