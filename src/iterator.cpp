#include "iterator.h"
#include "dfs_iterator.h"
#include "folder.h"
#include "node.h"

Folder::FolderIterator::FolderIterator(Folder *folder) : _folder(folder) {
}

void Folder::FolderIterator::first() {
  if (!enable) {
    throw "This iterator has been disabled";
  }
  _it = _folder->_nodes.begin();
}

Node *Folder::FolderIterator::currentItem() const {
  return *_it;
}

bool Folder::FolderIterator::isDone() const {
  return _it == _folder->_nodes.end();
}

void Folder::FolderIterator::next() {
  if (!enable) {
    throw "This iterator has been disabled";
  }
  _it++;
}

DfsIterator::DfsIterator(Node *folder) : _folder(folder) {
}

void DfsIterator::first() {
  currentIndex = 0;

  /* _vec.push_back(_folder); */
  dfsHelper(_folder);
}

void DfsIterator::dfsHelper(Node *folder) {
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
      dfsHelper(folder);
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
  bfsHelper();
}

void BfsIterator::bfsHelper() {
  while (!_q.empty()) {
    Node *node = _q.front();
    _q.pop();

    // dont push root directory
    if (node != _folder) {
      _vec.push_back(node);
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
