#pragma once

#include "folder.h"
#include "iterator.h"
#include "order_by.h"
#include "visitor.h"
#include <map>
#include <string>

using namespace std;

class TreeVisitor : public Visitor {
  private:
    OrderBy _orderBy;
    string _outString;
    int _currentLevel = 0;
    int _counter = 0;
    map<int, bool> _pipeIndent;

  public:
    TreeVisitor(OrderBy orderBy) : _orderBy(orderBy) {
    }

    void visitFile(File *file) {
    }

    string indent() {
        string finalIndent = "";
        for (int i = 0; i < _currentLevel; i++) {
            if (_pipeIndent[i]) {
                finalIndent += "│   ";
            } else {
                finalIndent += "    ";
            }
        }
        return finalIndent;
    }

    bool hasNextNode(Folder *folder) {
        return getParentFolderSize(folder) > _counter;
    }

    int getParentFolderSize(Node *folder) {
        Node *parant = folder->parent();
        int folderSize = 0;
        Iterator *it = parant->createIterator(OrderBy::Name);
        for (it->first(); !it->isDone(); it->next()) {
            folderSize++;
        }
        return folderSize;
    }

    void visitFolder(Folder *folder) {
        if (_currentLevel == 0) {
            _outString += ".\n";
        }
        if (_orderBy == OrderBy::Name) {
            _counter = 0;
            Iterator *it = folder->createIterator(OrderBy::Name);
            for (it->first(); !it->isDone(); it->next()) {
                _counter++;
                Node *node = it->currentItem();
                // print string according to `_currentLevel`
                _outString += indent() + "├── " + node->name() + "\n";

                // if it's a folder iterate again
                Folder *folder = dynamic_cast<Folder *>(node);
                if (folder) {
                    // check if has next node , if so, give map[level]=true
                    //	level up
                    if (hasNextNode(folder)) {
                        _pipeIndent[_currentLevel] = true;
                    }
                    _currentLevel++;
                    folder->accept(this);
                    //	level down
                    _currentLevel--;
                    _pipeIndent[_currentLevel] = false;
                }
            }
        }
    }

    string getTree() {
        return _outString;
    }
};
