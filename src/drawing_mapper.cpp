#include "drawing_mapper.h"
#include "sqlite_drawing_mapper.h"
#include "inmemory_drawing_mapper.h"
#include "db_mode.h"

DrawingMapper *DrawingMapper::instance() {
    mode m = DbMode::instance()->getMode();
    if (m == SQLite) {
        return SQLiteDrawingMapper::instance();
    }
    else {
        return InMemoryDrawingMapper::instance();
    }
}