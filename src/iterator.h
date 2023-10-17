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
  virtual ~Iterator(){};
  virtual void first() = 0;
  virtual Node *currentItem() const = 0;
  virtual void next() = 0;
  virtual bool isDone() const = 0;
};

#endif // ITERATOR_H
