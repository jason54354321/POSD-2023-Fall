#pragma once

#include <string>

using namespace std;

class JsonIterator;

class Value {
  public:
    virtual string toString() {
    }

    virtual JsonIterator *createIterator() = 0;
};
