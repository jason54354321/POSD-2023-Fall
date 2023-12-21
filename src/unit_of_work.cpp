#include "unit_of_work.h"
#include "drawing_mapper.h"
#include "painter_mapper.h"
#include "domain_object.h"
#include <list>
#include <iostream>


UnitOfWork * UnitOfWork::_instance = nullptr;

UnitOfWork::UnitOfWork() {
    
}

UnitOfWork * UnitOfWork::instance() {
    if(_instance == nullptr) {
        _instance = new UnitOfWork();
    }
    return _instance;
}

void UnitOfWork::registerNew(DomainObject * domainObject) {
        if(!inNew(domainObject->id())) {
            _new[domainObject->id()] = domainObject;
        }
        else {
            throw std::string("error");
        }
    }

void UnitOfWork::registerClean(DomainObject * domainObject) {
    std::string id = domainObject->id();
    if(!inClean(id) && !inDirty(id))
        _clean[id] = domainObject;
    if(!inClean(id) && inDirty(id))
        throw std::string("error");
}

void UnitOfWork::registerDirty(DomainObject * domainObject) {
    std::string id = domainObject->id();
    if(inNew(id) || inDirty(id)){
        return;
    }

    if(inClean(id)) {
        _dirty[id] = domainObject;
        _clean.erase(id);
        return;
    }
}

void UnitOfWork::registerDeleted(DomainObject * domainObject) {
    std::string id = domainObject->id();
    // not come from database
    if(inNew(id)){
        _new.erase(id);
        return;
    }

    if(inClean(id)) {
        _clean.erase(id);
        _deleted[id] = domainObject;
        return;
    }

    if(inDirty(id)) {
        _dirty.erase(id);
        _deleted[id] = domainObject;
        return;
    }
}

bool UnitOfWork::inNew(std::string id) const {
    return _new.count(id);
}

bool UnitOfWork::inClean(std::string id) const {
    return _clean.count(id);
}

bool UnitOfWork::inDirty(std::string id) const {
    return _dirty.count(id);
}

bool UnitOfWork::inDeleted(std::string id) const {
    return _deleted.count(id);
}

void UnitOfWork::commit() {
    for(auto dirty : _dirty) {
        if(Painter * p = dynamic_cast<Painter *>(dirty.second)){
            PainterMapper::instance()->update(p->id());
            _clean[p->id()] = p;
        } else if(Drawing * d = dynamic_cast<Drawing *>(dirty.second)){
            DrawingMapper::instance()->update(d->id());
            _clean[d->id()] = d;
        }
    }
    _dirty.clear();

    for(auto newbie : _new) {
        if(Painter * p = dynamic_cast<Painter *>(newbie.second)){
            PainterMapper::instance()->add(p);
            PainterMapper::instance()->find(p->id());
        } else if(Drawing * d = dynamic_cast<Drawing *>(newbie.second)){
            DrawingMapper::instance()->add(d);
            DrawingMapper::instance()->find(d->id());
        }
    }
    _new.clear();

    for(auto deleted : _deleted) {
        if(Painter * p = dynamic_cast<Painter *>(deleted.second)){
            PainterMapper::instance()->del(p->id());
        } else if(Drawing * d = dynamic_cast<Drawing *>(deleted.second)){
            DrawingMapper::instance()->del(d->id());
        }
    }
    _deleted.clear();
}