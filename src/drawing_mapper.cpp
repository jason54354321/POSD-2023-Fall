#include "drawing_mapper.h"

#include <sqlite3.h>
#include <string>
#include <map>
#include "drawing.h"
#include "parser.h"
#include "scanner.h"
#include "builder.h"
#include "painter_mapper.h"

DrawingMapper *DrawingMapper::_instance = nullptr;

Drawing *DrawingMapper::find(std::string id)
{
    return static_cast<Drawing *>(abstractFind(id, DrawingMapper::callback));
}

void DrawingMapper::add(DomainObject * Painter){
    abstractAdd(Painter);
}

void DrawingMapper::update(std::string id){
    abstractUpdate(getDomainObject(id));
}

void DrawingMapper::del(std::string id){
    abstractDelete(id);
}

std::string DrawingMapper::updateStmt(DomainObject * domainObject) const {
    Drawing* drawing = static_cast<Drawing*>(domainObject);
    std::string stmt = "UPDATE drawing SET painter='" + drawing->painter()->id() + "', shapes= '" + drawing->getShapesAsString() + "' WHERE ID='" + drawing->id() + "'";
    return stmt;
}

std::string DrawingMapper::addStmt(DomainObject * domainObject) const {
    Drawing* drawing = static_cast<Drawing*>(domainObject);

    
    std::string stmt = "INSERT INTO drawing"
                        "(ID, painter, shapes)"
                        "values"
                        "('" + drawing->id() + "', '" + drawing->painter()->id() + "', '" + drawing->getShapesAsString() + "')";

    return stmt;

}

std::string DrawingMapper::deleteByIdStmt(std::string id) const {
    std::cout << "delete by ID:" << id << std::endl;
    Drawing* painter = static_cast<Drawing*>(_domainObjects.at(id));
    std::string stmt = "DELETE FROM drawing WHERE ID='" + id + "'";
    return stmt;
}

std::string DrawingMapper::findByIdStmt(std::string id) const
{
    std::string stmt = "SELECT * FROM drawing WHERE ID = '" + id + "'";
    return stmt;
}

DrawingMapper *DrawingMapper::instance()
{
    if (_instance == nullptr)
    {
        _instance = new DrawingMapper();
    }
    return _instance;
}

int DrawingMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
    // build painter
    Painter *painter = PainterMapper::instance()->find(argv[1]);

    // build shapes
    std::list<Shape *>shapes = DrawingMapper::instance()->convertShapes(argc, argv);

    Drawing *drawing = new Drawing(argv[0], painter, shapes);

    DrawingMapper::instance()->load(drawing);
}

DrawingMapper::DrawingMapper()
{
    _builder = new Builder();
    _scanner = new Scanner();
    _parser = new Parser(_scanner, _builder);
}

std::list<Shape *> DrawingMapper::convertShapes(int argc, char **argv)
{
    _parser->clear();
    _parser->setInput(argv[2]);
    _parser->parse();
    return _parser->getShapes();
}