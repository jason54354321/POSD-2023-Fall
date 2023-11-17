#pragma once

#include "json_iterator.h"
#include "value.h"
#include "visitor.h"

class StringValue : public Value {
  private:
    string _value;

  public:
    StringValue(string value) : _value(value) {
    }

    string toString() override {
        return _value;
    }

    JsonIterator *createIterator() override {
        return new NullIterator();
    }

    void accept(JsonVisitor *visitor) override {
        visitor->visitStringValue(this);
    }
};
