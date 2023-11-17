#pragma once

#include "value.h"

class StringValue : public Value {
  private:
    string _value;

  public:
    StringValue(string value) : _value(value) {
    }

    string toString() override {
        return _value;
    }
};
