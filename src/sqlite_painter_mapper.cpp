#include "sqlite_painter_mapper.h"
#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"
#include "painter_mapper.h"
#include "sqlite_abstract_mapper.h"

SQLitePainterMapper* SQLitePainterMapper::_instance = nullptr;

Painter* SQLitePainterMapper::find(std::string id) {
    return static_cast<Painter *>(abstractFind(id, SQLitePainterMapper::callback));
}

// add
void SQLitePainterMapper::add(DomainObject * painter) {
    abstractAdd(painter);
}

// update
void SQLitePainterMapper::update(std::string id) {
    DomainObject * painter = getDomainObject(id);
    if(painter)
        abstractUpdate(painter);
    else
        throw std::string("object corresponding to ID is not in id map"); 
}

// delete
void SQLitePainterMapper::del(std::string id) {
    abstractDelete(id);
}

std::string SQLitePainterMapper::updateStmt(DomainObject * domainObject) const {
    Painter * painter = static_cast<Painter *>(domainObject);
    std::string stmt ("UPDATE painter SET ");
    stmt += "name = '" + painter->name() + "' "
            " where ID = '" + painter->id() + "'";
    return stmt;
}

std::string SQLitePainterMapper::findByIdStmt(std::string id) const {
    return "SELECT * FROM painter WHERE ID = '" + id + "'";
}

std::string SQLitePainterMapper::addStmt(DomainObject * domainObject) const {
    Painter * painter = static_cast<Painter *>(domainObject);
    std::string stmt = "INSERT INTO painter values (";
    stmt += "'" + painter->id() + "', ";
    stmt += "'" + painter->name() + "')";
    return stmt;
}

std::string SQLitePainterMapper::deleteByIdStmt(std::string id) const {
    return "DELETE FROM painter WHERE id = '" + id + "'";
}


SQLitePainterMapper* SQLitePainterMapper::instance() {
    if(_instance == nullptr) {
        _instance = new SQLitePainterMapper();
    }
    return _instance;
}

SQLitePainterMapper::SQLitePainterMapper(): SQLiteAbstractMapper("resource/painter.db") {
}

int SQLitePainterMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
    Painter* painter = new Painter(argv[0], argv[1]);
    SQLitePainterMapper::instance()->load(painter);
    return 0;
}

void SQLitePainterMapper::cleanCache() {
    SQLiteAbstractMapper::cleanCache();
}