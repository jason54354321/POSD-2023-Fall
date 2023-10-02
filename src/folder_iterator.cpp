#include "folder.h"
#include "iterator.h"

FolderIterator::FolderIterator(Folder *folder) : _folder(folder) {
}

void FolderIterator::first() {
  _it = _folder->nodes.begin();
}

Node *FolderIterator::currentItem() const {
  return *_it;
}

bool FolderIterator::isDone() const {
  return _it == _folder->nodes.end();
}

void FolderIterator::next() {
  _it++;
}
