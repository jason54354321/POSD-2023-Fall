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
  vector<Node *> _nodes;
  string _path;

public:
  Folder(string path) {
    _path = path;
  }

  void add(Node *node) override {
    _nodes.push_back(node);
  }

  void remove(string path) override {
    int index = -1;
    for (Node *node : _nodes) {
      index++;

      // ugly code
      File *file = dynamic_cast<File *>(node);
      if (file) {
        if (file->path() == path) {
          _nodes.erase(_nodes.begin() + index);
          return;
        }
      }

      Folder *folder = dynamic_cast<class Folder *>(node);
      if (folder) {
        folder->remove(path);
      }
    }
  }

  Node *getChildByName(const char *name) const override {
    for (Node *node : _nodes) {
      if (node->name() == name) {
        return node;
      }
    }
    return nullptr;
  }

  Node *find(string path) override {
    for (Node *node : _nodes) {
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
