#pragma once

#include "json_iterator.h"
#include "json_object.h"
#include "string_value.h"
#include "value.h"
#include "visitor.h"
#include <stack>

class JsonBuilder {
  private:
    stack<JsonObject *> _stack;
    JsonObject *last_pop;

  public:
    void buildValue(std::string key, std::string value) {
        Value *stringValue = new StringValue(value);

        _stack.top()->set(key, stringValue);
    }

    void buildObject(std::string key) {
        if (key == "") {
            JsonObject *object = new JsonObject();
            _stack.push(object);
        }
        JsonObject *object = new JsonObject();
        _stack.top()->set(key, object);
        _stack.push(object);
    }

    void endObject() {
        last_pop = _stack.top();
        _stack.pop();
    }

    JsonObject *getJsonObject() {
        JsonIterator *it = last_pop->createIterator();
        it->first();
        return dynamic_cast<JsonObject *>(it->currentValue());
    }
};
