#pragma once

#include "./file.h"
#include "./folder.h"
#include "./visitor.h"
#include "iterator.h"
#include <sstream>
#include <string>

class StreamOutVisitor : public Visitor {
private:
  string _streamOut;

public:
  StreamOutVisitor() {
  }

  void visitFile(File *file) override {
    // build
    stringstream ss;
    ss << "_____________________________________________" << endl;
    ss << file->path() << endl;
    ss << "---------------------------------------------" << endl;
    ss << file->getContext() << endl;
    ss << "_____________________________________________" << endl;

    string line;
    // convert to string
    while (std::getline(ss, line)) {
      std::cout << line << '\n';
    }
    _streamOut += ss.str() + '\n';
  }

  void visitFolder(Folder *folder) override {
    Iterator *it = folder->createIterator();
    for (it->first(); !it->isDone(); it->next()) {
      Node *node = it->currentItem();
      node->accept(this);
    }
  }

  string getResult() {
    // erase very last newline char
    if (_streamOut[_streamOut.length() - 1] == '\n') {
      _streamOut.erase(_streamOut.length() - 1);
    }
    return _streamOut;
  }
};
