#include "iterator.h"
#include "node.h"
#include <regex>
#include <string>
#include <vector>

#if !defined(FOLDER)
#define FOLDER

using namespace std;

class Folder : public Node {
  friend class FolderIterator;

private:
  vector<Node *> nodes;
  string _path;

public:
  Folder(string path) {
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

  Iterator *createIterator() override {
    return new FolderIterator(this);
  }
};

#endif // FOLDER
