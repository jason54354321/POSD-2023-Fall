#if !defined(FOLDER)
#define FOLDER

#include "file.h"
#include "iterator.h"
#include "node.h"
#include <iostream>
#include <regex>
#include <string>
#include <vector>

class Folder;

class Folder : public Node {
  friend class DfsIterator;
  friend class BfsIterator;

protected:
  vector<Node *> _nodes;
  vector<Iterator *> _iterators;

private:
  string _path;

  // a inner class, client won't know the existence of this class
  class FolderIterator : public Iterator {
  private:
    Folder *_folder;
    std::vector<Node *>::iterator _it;

  public:
    FolderIterator(Folder *folder);
    void first() override;
    Node *currentItem() const override;
    void next() override;
    bool isDone() const override;
  };

public:
  void validateSystemPath(string path) {
    struct stat sb;

    const char *pathcc = path.c_str();
    if (stat(pathcc, &sb) == -1) {
      cout << "Error when Folder new" << endl;
      throw "validation fail, no such file exist";
    }
  }

  Folder(string path) {
    validateSystemPath(path);
    _path = path;

    // TODO: OS
  }
  void disableExistIterator() {
    for (Iterator *it : _iterators) {
      it->enable = false;
    }
    _iterators.clear();
  }

  bool isPathLegit(Node *node) {
    string nodeFullPath = node->path();

    const regex regex("^(.*)\\/");
    smatch string_pieces;
    string nodeDirPath;

    regex_search(nodeFullPath, string_pieces, regex);
    if (string_pieces[1] == _path) {
      return true;
    }
    return false;
  }
  void add(Node *node) override {
    disableExistIterator();

    if (isPathLegit(node)) {
      _nodes.push_back(node);
    } else {
      throw "Invalid path exception";
    }
  }

  // TODO: delete ptr by dfsIterator
  void remove(string path) override {
    int index = -1;
    for (Node *node : _nodes) {
      index++;

      if (node->path() == path) {
        _nodes.erase(_nodes.begin() + index);
        /* delete node; */
        return;
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
    if (this->path() == path) {
      return this;
    }

    for (Node *node : _nodes) {
      if (!isNullPtr(node->find(path))) {
        return node->find(path);
      }
    }

    return nullptr;
  }

  bool isNullPtr(Node *node) {
    return node == nullptr;
  }

  int numberOfFiles() const override {
    int output = 0;
    for (Node *node : _nodes) {
      File *file = dynamic_cast<File *>(node);

      if (file) {
        output++;
      }

      Folder *folder = dynamic_cast<class Folder *>(node);
      if (folder) {
        output += folder->numberOfFiles();
      }
    }

    return output;
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

  // Memory leak? Who's responsibility to delete?
  Iterator *createIterator() override {
    Iterator *it = new FolderIterator(this);
    _iterators.push_back(it);
    return it;
  }
};

#endif // FOLDER
