#pragma once

#include <list>

class Node;
class Folder;

class Iterator {
protected:
  bool iterator_enable = true;

public:
  virtual void setEnable(bool enable) {
    iterator_enable = enable;
  }
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
