#include <gtest/gtest.h>

#include "../src/inmemory_painter_mapper.h"
#include "../src/inmemory_drawing_mapper.h"
#include "../src/drawing_mapper.h"
#include "../src/painter_mapper.h"
#include "../src/db_mode.h"

TEST(InMemorySuite, singleton){
    InMemoryPainterMapper *impm = InMemoryPainterMapper::instance();
    InMemoryDrawingMapper *imdm = InMemoryDrawingMapper::instance();
}


TEST(DB_MODE, thedefault) {
    ASSERT_EQ(SQLite, DbMode::instance()->getMode());
}

TEST(DB_MODE, inMemory) {
    DbMode::instance()->setMode(InMemory);
    ASSERT_EQ(InMemory, DbMode::instance()->getMode());

    DrawingMapper *dm = DrawingMapper::instance();
    PainterMapper *pm = PainterMapper::instance();

    pm->add(new Painter("01", "Jason"));

    Painter * painter = pm->find("01");
    ASSERT_EQ("Jason", painter->name());
}