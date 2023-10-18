#include "iterator.h"
#include "folder.h"

Folder::FolderIterator::FolderIterator(Folder *composite) : _host(composite) {
}

void Folder::FolderIterator::first() {
  if (!iterator_enable) {
    throw "This iterator has been disabled";
  }
  _current = _host->_nodes.begin();
}

Node *Folder::FolderIterator::currentItem() const {
  return *_current;
}

void Folder::FolderIterator::next() {
  if (!iterator_enable) {
    throw "This iterator has been disabled";
  }
  _current++;
}

bool Folder::FolderIterator::isDone() const {
  return _current == _host->_nodes.end();
}
