#include "iterator.h"
#include "node.h"
#include "visitor.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <sys/stat.h>

#if !defined(FILE_H)
#define FILE_H

using namespace std;
class File : public Node {
private:
  string _path;

  void validateSystemPath(string path) {
    struct stat sb;

    const char *pathcc = path.c_str();
    if (stat(pathcc, &sb) == -1) {
      cout << "Error when File new" << endl;
      throw "validation fail, no such file exist";
    }
  }

public:
  File(string path) {
    validateSystemPath(path);
    _path = path;
  }

  string getContext() {
    ifstream in(_path);

    stringstream buffer;
    buffer << in.rdbuf();

    string s = buffer.str();
    if (!s.empty() && s[s.length() - 1] == '\n') {
      s.erase(s.length() - 1);
    }
    return s;
  }

  Node *find(string path) override {
    if (this->path() == path) {
      return this;
    }
    return nullptr;
  }

  list<string> findByName(string name) override {
    std::list<string> pathList;
    if (this->name() == name) {
      pathList.push_back(this->path());
    }
    return pathList;
  }

  string path() const override {
    return _path;
  }

  string name() const override {
    const regex regex("[^\\/]+$");
    smatch string_pieces;

    if (regex_search(_path, string_pieces, regex)) {
      return string_pieces[0];
    }
    return "Regex found no string";
  }

  void accept(Visitor *visitor) override {
    visitor->visitFile(this);
  }
};

#endif // FILE_H
