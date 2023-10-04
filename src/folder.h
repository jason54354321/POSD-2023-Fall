#include <iostream>
#if !defined(FOLDER)
#define FOLDER

#include "file.h"
#include "iterator.h"
#include "node.h"
#include <regex>
#include <string>
#include <vector>

class Folder;

class Folder : public Node {
  friend class FolderIterator;

private:
  vector<Node *> nodes;
  string _path;

public:
  Folder(string path) {
    _path = path;
  }

  void add(Node *node) override {
    nodes.push_back(node);
  }

  void remove(string path) override {
    Iterator *it = this->createIterator();

    int index = -1;
    for (it->first(); !it->isDone(); it->next()) {
      index++;
      Node *node = it->currentItem();

      // ugly code
      File *file = dynamic_cast<File *>(node);
      if (file) {
        if (file->path() == path) {
          nodes.erase(nodes.begin() + index);
          return;
        }
      }

      Folder *folder = dynamic_cast<class Folder *>(node);
      if (folder) {
        folder->remove(path);
      }
    }
  }

  Node *find(string path) override {
    Iterator *it = this->createIterator();

    for (it->first(); !it->isDone(); it->next()) {
      Node *node = it->currentItem();

      // ugly code
      File *file = dynamic_cast<File *>(node);
      if (file) {
        if (file->path() == path) {
          return file;
        }
      }

      Folder *folder = dynamic_cast<class Folder *>(node);
      if (folder) {
        return folder->find(path);
      }
    }

    return nullptr;
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
