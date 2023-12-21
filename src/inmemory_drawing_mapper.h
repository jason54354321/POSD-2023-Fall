#pragma once

#include "drawing_mapper.h"
#include <map>
#include <string>

using namespace std;

class InMemoryDrawingMapper :public DrawingMapper{
public:
    static InMemoryDrawingMapper* instance();

    void add(DomainObject * Drawing);

    Drawing* find(std::string id);

    void update(std::string id);

    void del(std::string id);

    void cleanCache();

protected:
    std::list<Shape *> convertShapes(char * shape_string);

    std::string addStmt(DomainObject * domainObject) const;
    std::string findByIdStmt(std::string id) const;
    std::string updateStmt(DomainObject * domainObject) const;
    std::string deleteByIdStmt(std::string id) const;

private:
    static InMemoryDrawingMapper* _instance;
    map<string, Drawing*> _drawingMap;
};