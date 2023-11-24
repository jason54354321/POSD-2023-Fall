#pragma once

#include "json_iterator.h"
#include "json_object.h"
#include "string_value.h"
#include "value.h"
#include "visitor.h"
#include <stack>

class BeautifyVisitor : public JsonVisitor {
  private:
    stack<Value *> _stack;
    int _level = 0;
    string _outString;

  public:
    string indent() {
        string all_indent;
        for (int i = 0; i < _level; i++) {
            all_indent += "    ";
        }
        return all_indent;
    }
    void visitJsonObject(JsonObject *obj) {
        // init
        _outString += "{\n";
        _level++;
        visitorHelper(obj);
        _level--;
        _outString += "}";
    }

    void printKey(JsonIterator *it) {
        // print key
        _outString += indent();
        _outString += "\"";
        _outString += it->currentKey();
        _outString += "\"";
        _outString += ": ";
        return;
    }

    void visitorHelper(JsonObject *obj) {
        int counter = 0;
        JsonIterator *it = obj->createIterator();
        for (it->first(); !it->isDone(); it->next()) {
            counter++;
            // if it's a string_value, print the value
            StringValue *string_value = dynamic_cast<StringValue *>(it->currentValue());
            if (string_value) {
                printKey(it);
                _outString += string_value->toString();
                if (counter < obj->getMapSize()) {
                    _outString += ",\n";
                } else {
                    _outString += "\n";
                }
            }

            // if it's a object, iterate its child
            JsonObject *inner_obj = dynamic_cast<JsonObject *>(it->currentValue());
            if (inner_obj) {
                printKey(it);
                _outString += "{\n";
                _level++;
                /* inner_obj->accept(this); */
                visitorHelper(inner_obj);
                _level--;
                if (counter < obj->getMapSize()) {
                    _outString += indent() + "},\n";
                } else {
                    _outString += indent() + "}\n";
                }
            }
        }
        delete it;
    }

    void visitStringValue(StringValue *val) {
    }

    std::string getResult() const {
        return _outString;
    }
};
