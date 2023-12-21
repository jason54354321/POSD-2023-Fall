#include "drawing_mapper.h"
#include "sqlite_drawing_mapper.h"

DrawingMapper *DrawingMapper::instance() {
    return SQLiteDrawingMapper::instance();
}