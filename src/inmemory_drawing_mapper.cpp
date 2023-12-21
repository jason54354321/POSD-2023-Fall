#include "inmemory_drawing_mapper.h"

InMemoryDrawingMapper* InMemoryDrawingMapper::_instance = nullptr;

void InMemoryDrawingMapper::add(DomainObject* drawing) {
    Drawing* d= dynamic_cast<Drawing*>(drawing);
    _drawingMap[d->id()] = d;
}

Drawing* InMemoryDrawingMapper::find(std::string id) {
    return _drawingMap[id];
}

void InMemoryDrawingMapper::update(string id) {
}

void InMemoryDrawingMapper::del(string id) {
    _drawingMap.erase(id);
}

void InMemoryDrawingMapper::cleanCache() {
}

InMemoryDrawingMapper* InMemoryDrawingMapper::instance() {
    if(_instance == nullptr) {
        _instance = new InMemoryDrawingMapper();
    }
    return _instance;
}

std::list<Shape *> InMemoryDrawingMapper::convertShapes(char * shape_string) {

}

std::string InMemoryDrawingMapper::addStmt(DomainObject * domainObject) const {

}
std::string InMemoryDrawingMapper::findByIdStmt(std::string id) const {

}
std::string InMemoryDrawingMapper::updateStmt(DomainObject * domainObject) const {

}
std::string InMemoryDrawingMapper::deleteByIdStmt(std::string id) const {

}