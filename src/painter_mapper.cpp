#include "painter_mapper.h"
#include "sqlite_painter_mapper.h"

PainterMapper *PainterMapper::instance() {
    return SQLitePainterMapper::instance();
}