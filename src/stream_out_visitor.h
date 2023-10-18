#pragma once

#include "file.h"
#include "folder.h"
#include "iterator.h"
#include "visitor.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class StreamOutVisitor : public Visitor {
private:
  string _streamOut;

  string getContext(File *file) {
    ifstream in(file->path());

    stringstream buffer;
    buffer << in.rdbuf();

    string s = buffer.str();
    if (!s.empty() && s[s.length() - 1] == '\n') {
      s.erase(s.length() - 1);
    }
    return s;
  }

public:
  void visitFile(File *file) override {
    // build
    stringstream ss;
    ss << "_____________________________________________" << endl;
    ss << file->path() << endl;
    ss << "---------------------------------------------" << endl;
    ss << getContext(file) << endl;
    ss << "_____________________________________________" << endl;

    string line;
    // convert to string
    while (std::getline(ss, line)) {
      std::cout << line << '\n';
    }
    _streamOut += ss.str();
  }

  void visitFolder(Folder *folder) override {
    Iterator *it = folder->createIterator();
    for (it->first(); !it->isDone(); it->next()) {
      Node *node = it->currentItem();
      node->accept(this);
      File *file = dynamic_cast<File *>(node);
      if (file) {
        _streamOut += "\n";
      }
    }
  }

  string getResult() const {
    string holder = _streamOut;
    /* // erase very last newline char */
    /* if (holder[holder.length() - 1] == '\n') { */
    /*   holder.erase(holder.length() - 1); */
    /* } */
    return holder;
  }
};
