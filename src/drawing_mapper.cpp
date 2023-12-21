#include "drawing_mapper.h"

#include <sqlite3.h>
#include <string>
#include <map>
#include "drawing.h"
#include "triangle.h"
#include "parser.h"
#include "scanner.h"
#include "builder.h"
#include "domain_object.h"

DrawingMapper* DrawingMapper::_instance = nullptr;

Drawing* DrawingMapper::find(std::string id) {
    return static_cast<Drawing *>(abstractFind(id, DrawingMapper::callback));
}

// add
void DrawingMapper::add(DomainObject * drawing) {
    abstractAdd(drawing);
}

// update
void DrawingMapper::update(std::string id) {
    DomainObject * drawing = getDomainObject(id);
    if(drawing)
        abstractUpdate(drawing);
    else
        throw std::string("object corresponding to ID is not in id map");    
}

// delete
void DrawingMapper::del(std::string id) {
    abstractDelete(id);
}

std::string DrawingMapper::updateStmt(DomainObject * domainObject) const {
    Drawing * drawing = static_cast<Drawing *>(domainObject);
    std::string stmt ("UPDATE drawing SET ");
    stmt += "painter = '" + drawing->painter()->id() + "', "
            "shapes = '" + drawing->getShapesAsString() + "' "
            " WHERE ID = '" + drawing->id() + "'";
    return stmt;
}

std::string DrawingMapper::findByIdStmt(std::string id) const {
    std::string stmt = "SELECT * FROM drawing WHERE ID = '" + id + "'";
    return stmt;
}

std::string DrawingMapper::addStmt(DomainObject * domainObject) const {
    Drawing * drawing = static_cast<Drawing *>(domainObject);
    std::string stmt = "INSERT INTO drawing values (";
    stmt += "'" + drawing->id() + "', ";
    stmt += "'" + drawing->painter()->id() + "', ";
    stmt += "'" + drawing->getShapesAsString() + "')";
    return stmt;
}

std::string DrawingMapper::deleteByIdStmt(std::string id) const {
    return "DELETE FROM drawing WHERE id = '" + id + "'";
}


DrawingMapper* DrawingMapper::instance() {
    if(_instance == nullptr) {
        _instance = new DrawingMapper();
    }
    return _instance;
}

DrawingMapper::DrawingMapper(): SQLiteAbstractMapper("resource/drawing.db") {
    _parser = new Parser(new Scanner(), new Builder());
}

int DrawingMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
    Painter * painter = PainterMapper::instance()->find(argv[1]);
    std::list<Shape *> shapes = DrawingMapper::instance()->convertShapes(argv[2]);
    Drawing * drawing = new Drawing(argv[0], painter, shapes);
    DrawingMapper::instance()->load(drawing);
    return 0;
}

std::list<Shape *> DrawingMapper::convertShapes(char * shape_string) {
    _parser->clear();
    _parser->setInput(shape_string);
    _parser->parse();
    return _parser->getShapes();
}

void DrawingMapper::cleanCache() {
    SQLiteAbstractMapper::cleanCache();
    _parser->clear();
}