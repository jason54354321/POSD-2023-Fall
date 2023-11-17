#pragma once

#include "json_iterator.h"
#include "value.h"
#include <map>
#include <string>

class JsonObject : public Value {
    friend class JsonObjectIterator;

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
    };

    string toString() override {
    }

    Value *getValue(string key) {
        return _map[key];
    }

    void set(string key, Value *value) {
        _map[key] = value;
    }

    JsonObjectIterator *createIterator() {
        return new JsonObjectIterator(this);
    }
};
