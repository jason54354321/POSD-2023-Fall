#pragma once

#include <string>

#include <sqlite3.h>

#include "sqlite_abstract_mapper.h"
#include "drawing_mapper.h"

class Drawing;
class Parser;
class Builder;
class Scanner;
class PainterMapper;

class SQLiteDrawingMapper: public SQLiteAbstractMapper, public DrawingMapper {
public:

    ~SQLiteDrawingMapper() {
        delete _parser;
    }

    void add(DomainObject * Drawing);

    Drawing* find(std::string id);

    void update(std::string id);

    void del(std::string id);

    static SQLiteDrawingMapper* instance();

    void cleanCache();

protected:
    SQLiteDrawingMapper();

    static int callback(void* notUsed, int argc, char** argv, char** colNames);

    std::list<Shape *> convertShapes(char * shape_string);

    std::string addStmt(DomainObject * domainObject) const;
    std::string findByIdStmt(std::string id) const;
    std::string updateStmt(DomainObject * domainObject) const;
    std::string deleteByIdStmt(std::string id) const;

private:
    static SQLiteDrawingMapper* _instance;
    Parser * _parser;
};