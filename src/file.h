#include "node.h"
#include <iostream>
#include <regex>
#include <string>
#if !defined(FILE_H)
#define FILE_H

using namespace std;
class File : public Node {
private:
  string _path;

public:
  File(string path) {
    _path = path;
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
};

#endif // FILE_H
