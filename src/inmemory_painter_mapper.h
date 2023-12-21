#pragma once

#include "painter_mapper.h"
#include <map>
#include <string>

using namespace std;

class InMemoryPainterMapper: public PainterMapper {
public:
    static InMemoryPainterMapper* instance();

    void add(DomainObject * Painter);

    Painter* find(std::string id);

    void update(std::string id);

    void del(std::string id);

    void cleanCache();

protected:
    std::string addStmt(DomainObject * domainObject) const;
    std::string findByIdStmt(std::string id) const;
    std::string updateStmt(DomainObject * domainObject) const;
    std::string deleteByIdStmt(std::string id) const;

private:
    static InMemoryPainterMapper* _instance;
    map<string, Painter*> _painterMap;
};