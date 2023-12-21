#pragma once

#include <string>

enum mode {
    SQLite,
    InMemory
};

class DbMode {
public:
    static DbMode * instance();

    void setMode(mode dbMode);

    mode getMode();

private:
    DbMode();

    mode _dbMode;

    static DbMode * _instance;
};
