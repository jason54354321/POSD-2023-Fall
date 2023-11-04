#pragma once

#include "folder.h"
#include "iterator.h"
#include "order_by.h"
#include "visitor.h"
#include <string>

using namespace std;

class TreeVisitor : public Visitor {
  private:
    OrderBy _orderBy;
    string _treeString;
    int _currentLevel;

  public:
    TreeVisitor(OrderBy orderBy) : _orderBy(orderBy) {
    }

    void visitFile(File *file);
    void visitFolder(Folder *folder) {
        if (_orderBy == OrderBy::Name) {
            Iterator *it = folder->createIterator(OrderBy::Name);
            for (it->first(); !it->isDone(); it->isDone()) {
                // print string according to `_currentLevel`

                // if it's a folder interate again
            }
        }
    }

    string getTree();
};
