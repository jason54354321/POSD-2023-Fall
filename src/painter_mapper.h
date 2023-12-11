#pragma once

#include <string>
#include <sqlite3.h>

#include "abstract_mapper.h"

class Painter;

class PainterMapper: public AbstractMapper {
public:
    Painter* find(std::string id);
    
    void add(DomainObject * Painter);

    void update(std::string id);

    void del(std::string id);

    std::string updateStmt(DomainObject * domainObject) const override;

    std::string findByIdStmt(std::string id) const override;

    std::string addStmt(DomainObject * domainObject) const override;

    std::string deleteByIdStmt(std::string id) const override;

    static PainterMapper* instance();

protected:
    PainterMapper();

    static int callback(void* notUsed, int argc, char** argv, char** colNames);
    
private:
    char* _errorMessage;
    static PainterMapper* _instance;
};