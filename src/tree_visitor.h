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
    map<int, int> _counter;
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

    bool hasNextNode(Node *folder) {
        cout << "Named:" << folder->name() << "'s parent has " << getParentFolderSize(folder)
             << "item";
        cout << ", and the _counter:" << _counter[_currentLevel] << endl;
        return getParentFolderSize(folder) > _counter[_currentLevel];
    }

    int getParentFolderSize(Node *folder) {
        Node *parant = folder->parent();
        int folderSize = 0;
        Iterator *it = parant->createIterator();
        for (it->first(); !it->isDone(); it->next()) {
            folderSize++;
        }
        return folderSize;
    }

    void visitFolderHelper(Iterator *it) {
        for (it->first(); !it->isDone(); it->next()) {
            _counter[_currentLevel]++;
            Node *node = it->currentItem();
            // print string according to `_currentLevel`
            if (hasNextNode(node)) {
                _outString += indent() + "├── " + node->name() + "\n";
            } else {
                _outString += indent() + "└── " + node->name() + "\n";
            }

            // if it's a folder iterate again
            Folder *inner_folder = dynamic_cast<Folder *>(node);
            if (inner_folder) {
                // check if has next node , if so, give map[level]=true
                //	level up
                if (hasNextNode(inner_folder)) {
                    _pipeIndent[_currentLevel] = true;
                }
                _currentLevel++;
                inner_folder->accept(this);
                //	level down: init currentLevel's temp data
                _pipeIndent[_currentLevel] = false;
                _counter[_currentLevel] = 0;
                _currentLevel--;
            }
        }
    }

    void visitFolder(Folder *folder) {
        if (_currentLevel == 0) {
            _outString += ".\n";
        }
        Iterator *it = folder->createIterator(_orderBy);
        visitFolderHelper(it);
    }

    string getTree() {
        return _outString;
    }
};
