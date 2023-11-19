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
    JsonObject *root;

  public:
    void buildValue(std::string key, std::string value) {
        cout << "building Value: " << key << "+" << value << endl;
        Value *stringValue = new StringValue(value);

        _stack.top()->set(key, stringValue);
    }

    void buildObject(std::string key) {
        cout << "building Object: " << key << endl;
        if (key == "") {
            root = new JsonObject();
            _stack.push(root);
            return;
        }
        JsonObject *object = new JsonObject();
        _stack.top()->set(key, object);
        _stack.push(object);
    }

    void endObject() {
        if (_stack.empty()) {
            return;
        }
        cout << "ending Object: " << _stack.top() << endl;
        _stack.pop();
    }

    JsonObject *getJsonObject() {
        cout << "getJsonObject" << root << endl;
        return root;
    }
};
