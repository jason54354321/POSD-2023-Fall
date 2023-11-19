#pragma once

#include "json_iterator.h"
#include "value.h"
#include "visitor.h"
#include <map>
#include <sstream>
#include <string>

class JsonObject : public Value {
  private:
    std::map<string, Value *> _map;

  public:
    class JsonObjectIterator : public JsonIterator {
      private:
        map<string, Value *>::iterator _it;
        JsonObject *_json_object;

      public:
        JsonObjectIterator(JsonObject *json_object) : _json_object(json_object) {
        }

        void first() override {
            _it = _json_object->_map.begin();
        }

        void next() override {
            _it++;
        }

        bool isDone() const override {
            return _it == _json_object->_map.end();
        }

        string currentKey() const override {
            return _it->first;
        }

        Value *currentValue() const override {
            return _it->second;
        }
    };

    int getMapSize() const {
        return _map.size();
    }

    string toString() override {
        stringstream ss;
        ss << "{\n";

        int count = 0;
        for (auto m : _map) {
            count++;
            ss << "\"" << m.first << "\":\"" << m.second->toString() << "\""
               << "\n";
            if (count < _map.size()) ss << ",";
        }

        ss << "\n}";

        return ss.str();
    }

    Value *getValue(string key) {
        return _map[key];
    }

    void set(string key, Value *value) {
        _map[key] = value;
    }

    JsonIterator *createIterator() override {
        return new JsonObjectIterator(this);
    }

    void accept(JsonVisitor *visitor) override {
        visitor->visitJsonObject(this);
    }
};
