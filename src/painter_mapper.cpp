#include "painter_mapper.h"
#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"
#include "sqlite_abstract_mapper.h"

PainterMapper* PainterMapper::_instance = nullptr;

Painter* PainterMapper::find(std::string id) {
    return static_cast<Painter *>(abstractFind(id, PainterMapper::callback));
}

// add
void PainterMapper::add(DomainObject * painter) {
    abstractAdd(painter);
}

// update
void PainterMapper::update(std::string id) {
    DomainObject * painter = getDomainObject(id);
    if(painter)
        abstractUpdate(painter);
    else
        throw std::string("object corresponding to ID is not in id map"); 
}

// delete
void PainterMapper::del(std::string id) {
    abstractDelete(id);
}

std::string PainterMapper::updateStmt(DomainObject * domainObject) const {
    Painter * painter = static_cast<Painter *>(domainObject);
    std::string stmt ("UPDATE painter SET ");
    stmt += "name = '" + painter->name() + "' "
            " where ID = '" + painter->id() + "'";
    return stmt;
}

std::string PainterMapper::findByIdStmt(std::string id) const {
    return "SELECT * FROM painter WHERE ID = '" + id + "'";
}

std::string PainterMapper::addStmt(DomainObject * domainObject) const {
    Painter * painter = static_cast<Painter *>(domainObject);
    std::string stmt = "INSERT INTO painter values (";
    stmt += "'" + painter->id() + "', ";
    stmt += "'" + painter->name() + "')";
    return stmt;
}

std::string PainterMapper::deleteByIdStmt(std::string id) const {
    return "DELETE FROM painter WHERE id = '" + id + "'";
}


PainterMapper* PainterMapper::instance() {
    if(_instance == nullptr) {
        _instance = new PainterMapper();
    }
    return _instance;
}

PainterMapper::PainterMapper(): SQLiteAbstractMapper("resource/painter.db") {
}

int PainterMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
    Painter* painter = new Painter(argv[0], argv[1]);
    PainterMapper::instance()->load(painter);
    return 0;
}

void PainterMapper::cleanCache() {
    SQLiteAbstractMapper::cleanCache();
}