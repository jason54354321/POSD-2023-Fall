#pragma once

#include <string>

#include "folder.h"
#include <stack>

using std::string;

class FileSystemBuilder {
  private:
    stack<Folder *> _stack;
    Folder *_root;

  public:
    Folder *getRoot() const {
        return _stack.top();
    }

    void buildFile(string path) {
        _stack.top()->add(new File(path));
    }

    void buildFolder(string path) {
        Folder *folder = new Folder(path);
        _stack.push(folder);
    }

    void endFolder() {
        if (_stack.size() == 1) {
            return;
        }
        cout << "end folder:" << endl;
        Folder *inner_folder = _stack.top();
        _stack.pop();
        Folder *outter_folder = _stack.top();
        outter_folder->add(inner_folder);
    }
};
