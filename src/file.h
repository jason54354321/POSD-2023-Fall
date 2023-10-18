#pragma once

#include "node.h"
#include <iostream>
#include <sys/stat.h>

class File : public Node {
private:
  void validateSystemPath(string path) {
    struct stat sb;

    const char *pathcc = path.c_str();
    if (stat(pathcc, &sb) == -1) {
      cout << "Error when File new" << endl;
      throw "validation fail, no such file exist";
    }

    string filetype;
    if ((sb.st_mode & S_IFMT) != S_IFREG) {
      cout << "Error when File new" << endl;
      throw "validation fail, no such file exist";
    }
  }

public:
  File(string path) : Node(path) {
    validateSystemPath(path);
  }

  int numberOfFiles() const {
    return 1;
  }

  Node *find(string path) {
    if (this->path() == path) {
      return this;
    }
    return nullptr;
  }

  std::list<string> findByName(string name) override {
    std::list<string> pathList;
    if (this->name() == name) {
      pathList.push_back(this->path());
    }
    return pathList;
  }

  void accept(Visitor *visitor) override {
    visitor->visitFile(this);
  }
};
