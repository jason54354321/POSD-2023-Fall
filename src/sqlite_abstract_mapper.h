#pragma once

#include <sqlite3.h>
#include <unordered_map>
#include <iostream>
#include "domain_object.h"
#include "unit_of_work.h"
#include "drawing.h"

typedef int (*CallbackType)(void *, int argc, char **argv, char **col_names);

class SQLiteAbstractMapper {
public:
    SQLiteAbstractMapper(std::string db_file) {
        sqlite3_open(db_file.c_str(), &_db);
    }
    
    virtual ~SQLiteAbstractMapper() {
        sqlite3_close(_db);
    }


    bool isLoaded(const std::string &id) const {
        return _domainObjects.count(id);
    }

    virtual void cleanCache() {
        _domainObjects.clear();
    }

protected:

    virtual std::string addStmt(DomainObject *domainObject) const = 0;
    virtual std::string findByIdStmt(std::string id) const = 0;
    virtual std::string updateStmt(DomainObject *domainObject) const = 0;
    virtual std::string deleteByIdStmt(std::string id) const = 0;

    DomainObject *getDomainObject(std::string id) {
        if (_domainObjects.count(id)) {
            return _domainObjects.at(id);
        }
        return nullptr;
    }

    void abstractAdd(DomainObject *domainObject) {
        int rc = sqlite3_exec(_db, addStmt(domainObject).c_str(), NULL, NULL, &_errorMessage);
        if (rc) {
            std::cout << "Add SQL error: " << _errorMessage << std::endl;
            sqlite3_free(_errorMessage);
        }
    }

    DomainObject * abstractFind(std::string id, CallbackType callback) {
        auto it = _domainObjects.find(id);

        if (it != _domainObjects.end()) {
            return it->second;
        }

        int rc = sqlite3_exec(_db, findByIdStmt(id).c_str(), callback, NULL, &_errorMessage);
        if (rc) {
            std::cout << "Find SQL error: " << _errorMessage << std::endl;
            sqlite3_free(_errorMessage);
        }

        if (isLoaded(id)) {
            UnitOfWork::instance()->registerClean(_domainObjects.at(id));
            return _domainObjects.at(id);
        }
        else {
            return nullptr;
        }
    }

    void abstractUpdate(DomainObject *domainObject) {
        int rc = sqlite3_exec(_db, updateStmt(domainObject).c_str(), NULL, NULL, &_errorMessage);
        if (rc) {
            std::cout << "Update SQL error: " << _errorMessage << std::endl;
            sqlite3_free(_errorMessage);
        }
    }

    void abstractDelete(std::string id) {
        int rc = sqlite3_exec(_db, deleteByIdStmt(id).c_str(), NULL, NULL, &_errorMessage);
        if (rc) {
            std::cout << "Delete SQL error: " << _errorMessage << std::endl;
            sqlite3_free(_errorMessage);
        }
        if (_domainObjects.count(id)) {
            delete _domainObjects.at(id);
            _domainObjects.erase(id);
        } 
    }

    void load(DomainObject *domainObject) {
        if (isLoaded(domainObject->id())) {
            return;
        }
        _domainObjects[domainObject->id()] = domainObject;
    }

private:
    std::unordered_map<std::string, DomainObject *> _domainObjects;
    sqlite3 *_db;
    char* _errorMessage;
};