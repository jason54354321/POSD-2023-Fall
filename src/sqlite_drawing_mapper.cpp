#include "sqlite_drawing_mapper.h"

#include <sqlite3.h>
#include <string>
#include <map>
#include "drawing.h"
#include "triangle.h"
#include "parser.h"
#include "scanner.h"
#include "builder.h"
#include "domain_object.h"
#include "painter_mapper.h"

SQLiteDrawingMapper* SQLiteDrawingMapper::_instance = nullptr;

Drawing* SQLiteDrawingMapper::find(std::string id) {
    return static_cast<Drawing *>(abstractFind(id, SQLiteDrawingMapper::callback));
}

// add
void SQLiteDrawingMapper::add(DomainObject * drawing) {
    abstractAdd(drawing);
}

// update
void SQLiteDrawingMapper::update(std::string id) {
    DomainObject * drawing = getDomainObject(id);
    if(drawing)
        abstractUpdate(drawing);
    else
        throw std::string("object corresponding to ID is not in id map");    
}

// delete
void SQLiteDrawingMapper::del(std::string id) {
    abstractDelete(id);
}

std::string SQLiteDrawingMapper::updateStmt(DomainObject * domainObject) const {
    Drawing * drawing = static_cast<Drawing *>(domainObject);
    std::string stmt ("UPDATE drawing SET ");
    stmt += "painter = '" + drawing->painter()->id() + "', "
            "shapes = '" + drawing->getShapesAsString() + "' "
            " WHERE ID = '" + drawing->id() + "'";
    return stmt;
}

std::string SQLiteDrawingMapper::findByIdStmt(std::string id) const {
    std::string stmt = "SELECT * FROM drawing WHERE ID = '" + id + "'";
    return stmt;
}

std::string SQLiteDrawingMapper::addStmt(DomainObject * domainObject) const {
    Drawing * drawing = static_cast<Drawing *>(domainObject);
    std::string stmt = "INSERT INTO drawing values (";
    stmt += "'" + drawing->id() + "', ";
    stmt += "'" + drawing->painter()->id() + "', ";
    stmt += "'" + drawing->getShapesAsString() + "')";
    return stmt;
}

std::string SQLiteDrawingMapper::deleteByIdStmt(std::string id) const {
    return "DELETE FROM drawing WHERE id = '" + id + "'";
}


SQLiteDrawingMapper* SQLiteDrawingMapper::instance() {
    if(_instance == nullptr) {
        _instance = new SQLiteDrawingMapper();
    }
    return _instance;
}

SQLiteDrawingMapper::SQLiteDrawingMapper(): SQLiteAbstractMapper("resource/drawing.db") {
    _parser = new Parser(new Scanner(), new Builder());
}

int SQLiteDrawingMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
    Painter * painter = PainterMapper::instance()->find(argv[1]);
    std::list<Shape *> shapes = SQLiteDrawingMapper::instance()->convertShapes(argv[2]);
    Drawing * drawing = new Drawing(argv[0], painter, shapes);
    SQLiteDrawingMapper::instance()->load(drawing);
    return 0;
}

std::list<Shape *> SQLiteDrawingMapper::convertShapes(char * shape_string) {
    _parser->clear();
    _parser->setInput(shape_string);
    _parser->parse();
    return _parser->getShapes();
}

void SQLiteDrawingMapper::cleanCache() {
    SQLiteAbstractMapper::cleanCache();
    _parser->clear();
}