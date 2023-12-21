#pragma once

#include <string>

#include <sqlite3.h>

#include "drawing.h"
#include "sqlite_abstract_mapper.h"

class Parser;
class Builder;
class Scanner;
class PainterMapper;

class DrawingMapper{
public:
    virtual void add(DomainObject * Drawing) = 0;

    virtual Drawing* find(std::string id) = 0;

    virtual void update(std::string id) = 0;

    virtual void del(std::string id) = 0;

    static DrawingMapper* instance();

    virtual void cleanCache() = 0;

protected:
    DrawingMapper() {};

    static int callback(void* notUsed, int argc, char** argv, char** colNames);

    virtual std::list<Shape *> convertShapes(char * shape_string) = 0;

    virtual std::string addStmt(DomainObject * domainObject) const = 0;
    virtual std::string findByIdStmt(std::string id) const = 0;
    virtual std::string updateStmt(DomainObject * domainObject) const = 0;
    virtual std::string deleteByIdStmt(std::string id) const = 0;
};