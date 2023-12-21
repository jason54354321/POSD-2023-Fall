#include "painter_mapper.h"
#include "sqlite_painter_mapper.h"
#include "inmemory_painter_mapper.h"
#include "db_mode.h"

PainterMapper *PainterMapper::instance() {
    mode m = DbMode::instance()->getMode();
    if (m == SQLite) {
        return SQLitePainterMapper::instance();
    }
    else {
        return InMemoryPainterMapper::instance();
    }
}