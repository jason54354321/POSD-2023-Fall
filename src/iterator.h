#if !defined(ITERATOR_H)
#define ITERATOR_H

#include "node.h"
#include <list>
#include <vector>

#pragma once

class Folder;

class Iterator {
public:
  bool enable = true;
  virtual ~Iterator() {
  }
  virtual void first() {
  }
  virtual Node *currentItem() const {
    return nullptr;
  }
  virtual void next() {
  }
  virtual bool isDone() const {
    return true;
  }
};

#endif // ITERATOR_H
