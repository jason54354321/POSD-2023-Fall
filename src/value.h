#pragma once

#include <string>

using namespace std;

class JsonIterator;
class JsonVisitor;

class Value {
  public:
    virtual string toString() {
    }

    virtual JsonIterator *createIterator() = 0;
    virtual void accept(JsonVisitor *visitor) = 0;
};
