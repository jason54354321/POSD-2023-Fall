#include "folder.h"
#include "iterator.h"

FolderIterator::FolderIterator(Folder *folder) : _folder(folder) {
}

void FolderIterator::first() {
  _it = _folder->nodes.begin();
}

bool FolderIterator::isDone() const {
  return _it == _folder->nodes.end();
}
