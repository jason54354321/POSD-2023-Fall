#include "inmemory_painter_mapper.h"
#include "painter.h"
#include "domain_object.h"

InMemoryPainterMapper* InMemoryPainterMapper::_instance = nullptr;

void InMemoryPainterMapper::add(DomainObject* painter) {
    Painter* p= dynamic_cast<Painter*>(painter);
    _painterMap[p->id()] = p;
}

Painter* InMemoryPainterMapper::find(std::string id) {
    return _painterMap[id];
}

void InMemoryPainterMapper::update(string id) {
}

void InMemoryPainterMapper::del(string id) {
    _painterMap.erase(id);
}

void InMemoryPainterMapper::cleanCache() {
}

std::string InMemoryPainterMapper::addStmt(DomainObject * domainObject) const {

}
std::string InMemoryPainterMapper::findByIdStmt(std::string id) const {

}
std::string InMemoryPainterMapper::updateStmt(DomainObject * domainObject) const {

}
std::string InMemoryPainterMapper::deleteByIdStmt(std::string id) const {

}

InMemoryPainterMapper* InMemoryPainterMapper::instance() {
    if(_instance == nullptr) {
        _instance = new InMemoryPainterMapper();
    }
    return _instance;
}