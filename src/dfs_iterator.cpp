#include "dfs_iterator.h"
#include "folder.h"
#include "node.h"
#include <iostream>

DfsIterator::DfsIterator(Node *folder) : _folder(folder) {
}

void DfsIterator::first() {
  currentIndex = 0;

  _vec.push_back(_folder);
  helper(_folder);
}

void DfsIterator::helper(Node *folder) {
  Iterator *it = folder->createIterator();
  for (it->first(); !it->isDone(); it->next()) {
    Node *node = it->currentItem();

    File *file = dynamic_cast<File *>(node);
    if (file) {
      _vec.push_back(file);
    }

    Folder *folder = dynamic_cast<Folder *>(node);
    if (folder) {
      _vec.push_back(folder);
      helper(folder);
    }
  }
}

Node *DfsIterator::currentItem() const {
  return _vec[currentIndex];
}

void DfsIterator::next() {
  currentIndex++;
}

bool DfsIterator::isDone() const {
  return currentIndex == _vec.size();
}

Iterator::~Iterator() {
}

BfsIterator::BfsIterator(Node *folder) : _folder(folder) {
}

void BfsIterator::first() {
  _q.push(_folder);
}

void BfsIterator::helper() {
  while (!_q.empty()) {
    Node *node = _q.front();
    _q.pop();

    File *file = dynamic_cast<File *>(node);
    if (file) {
      _q.push(file);
    }

    Folder *folder = dynamic_cast<Folder *>(node);
    if (folder) {
      Iterator *it = folder->createIterator();
      for (it->first(); !it->isDone(); it->next()) {
        _q.push(it->currentItem());
      }
    }
  }
}

Node *BfsIterator::currentItem() const {
  return _vec[currentIndex];
}

void BfsIterator::next() {
  currentIndex++;
}

bool BfsIterator::isDone() const {
  return currentIndex == _vec.size();
}
