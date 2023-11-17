#pragma once
#include <map>
#include <string>

class Value;

using namespace std;

class JsonIterator {
  public:
    virtual void first() = 0;

    virtual string currentKey() const = 0;

    virtual Value *currentValue() const = 0;

    virtual void next() = 0;
    virtual bool isDone() const = 0;
};

class NullIterator : public JsonIterator {};
