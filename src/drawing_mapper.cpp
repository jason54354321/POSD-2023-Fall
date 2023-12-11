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

}

void DrawingMapper::update(std::string id){

}

void DrawingMapper::del(std::string id){

}

std::string DrawingMapper::updateStmt(DomainObject * domainObject) const {

}

std::string DrawingMapper::addStmt(DomainObject * domainObject) const {

}

std::string DrawingMapper::deleteByIdStmt(std::string id) const {

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
    Scanner *scanner = new Scanner();
    Builder * builder = new Builder();
    Parser *parser = new Parser(scanner, builder);
    parser->setInput(argv[2]);
    parser->parse();
    std::list<Shape *>shapes = parser->getShapes();

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