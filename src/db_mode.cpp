#include <string>
#include "db_mode.h"

DbMode * DbMode::_instance = nullptr;

DbMode * DbMode::instance() {
    if (_instance == nullptr) {
        _instance = new DbMode();
    }
    return _instance;
}

void DbMode::setMode(mode dbMode) {
    _dbMode = dbMode;
}

mode DbMode::getMode() {
    return _dbMode;
}

DbMode::DbMode(): _dbMode(SQLite) {}
