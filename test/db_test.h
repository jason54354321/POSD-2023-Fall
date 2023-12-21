#include <gtest/gtest.h>
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <list>
#include "../src/unit_of_work.h"
#include "../src/drawing_mapper.h"
#include "../src/drawing.h"
#include "../src/triangle.h"
#include "../src/shape.h"
#include "../src/painter.h"
#include <memory>

class DBSuite : public ::testing::Test {
protected:
    void SetUp() override {
        create_drawing_table();
        create_painter_table();
        populate_drawings();
        populate_painters();
        dm = DrawingMapper::instance();
        dm->cleanCache();
        pm = PainterMapper::instance();
        pm->cleanCache();
    }

    void TearDown() override {
        drop_drawing_table();
        drop_painter_table();
        sqlite3_close(db);
        sqlite3_close(db_p);
    }

    void create_drawing_table() {
        ASSERT_EQ(0, sqlite3_open("resource/drawing.db", &db));
        const char *stmt = "CREATE TABLE drawing ("
                           "ID         char(6) PRIMARY KEY     not null,"
                           "painter    varchar(50)             not null,"
                           "shapes varchar(1028),"
                           "FOREIGN KEY(painter) REFERENCES painter(ID))";
        int rc = sqlite3_exec(db, stmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void drop_drawing_table() {
        const char *dropStmt = "DROP TABLE drawing";
        int rc = sqlite3_exec(db, dropStmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void create_painter_table() {
        ASSERT_EQ(0, sqlite3_open("resource/painter.db", &db_p));
        const char *stmt = "CREATE TABLE painter ("
                           "ID         char(6) PRIMARY KEY     not null,"
                           "name    varchar(50)             not null)";
        int rc = sqlite3_exec(db_p, stmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void drop_painter_table() {
        const char *dropStmt = "DROP TABLE painter";
        int rc = sqlite3_exec(db_p, dropStmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void populate_drawings() {
        const char *s1 = "INSERT INTO drawing"
                         "(ID, painter, shapes)"
                         "values"
                         "('d_0001', 'p_0001', 'triangle 1 1 1')";
        int rc = sqlite3_exec(db, s1, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s2 = "INSERT INTO drawing"
                         "(ID,  painter,   shapes)"
                         "values"
                         "('d_0002', 'p_0001', 'triangle 2 2 2')";
        rc = sqlite3_exec(db, s2, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s3 = "INSERT INTO drawing"
                         "(ID,  painter,   shapes)"
                         "values"
                         "('d_0003', 'p_0002', 'compound { triangle 1 1 1 triangle 2 2 2 } triangle 3 3 3')";
        rc = sqlite3_exec(db, s3, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);
    }

    void populate_painters() {
        const char *s1 = "INSERT INTO painter"
                         "(ID, name)"
                         "values"
                         "('p_0001', 'Patrick')";
        int rc = sqlite3_exec(db_p, s1, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s2 = "INSERT INTO painter"
                         "(ID, name)"
                         "values"
                         "('p_0002', 'Mary')";
        rc = sqlite3_exec(db_p, s2, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);
    }

    void display_err_msg_and_fail_if_any(int rc) {
        if (rc) {
            std::cout << "db error: " << err_msg << std::endl;
            sqlite3_free(err_msg);
        }
        ASSERT_EQ(SQLITE_OK, rc);
    }

    sqlite3 * db;
    sqlite3 * db_p;
    char * err_msg = nullptr;
    DrawingMapper * dm;
    PainterMapper * pm;
};

// ensure db setup teardown works alone
TEST_F(DBSuite, Sanity) {
}

// new
TEST_F(DBSuite, NewDrawingAndPainterThroughUoWAndFind) {
    UnitOfWork *uow = UnitOfWork::instance();
    Painter *painter = new Painter("p_0004", "Richard");
    uow->registerNew(painter);
    EXPECT_TRUE(uow->inNew(painter->id()));
    std::list<Shape *> shapes;
    shapes.push_back(new Triangle(2, 2, 3));
    shapes.push_back(new Triangle(4, 4, 4));
    shapes.push_back(new Triangle(9, 7, 5));
    Drawing *drawing = new Drawing("d_0005", painter, shapes);
    uow->registerNew(drawing);
    EXPECT_TRUE(uow->inNew(drawing->id()));
    uow->commit();

    dm->cleanCache();
    pm->cleanCache();
    Drawing * d = dm->find("d_0005");
    EXPECT_TRUE(uow->inClean(d->id()));
    ASSERT_EQ("p_0004", d->painter()->id());
    ASSERT_EQ("Richard", d->painter()->name());
    ASSERT_EQ("d_0005", d->id());
    ASSERT_EQ(7, d->getShape(0)->perimeter());
    ASSERT_EQ(12, d->getShape(1)->perimeter());
    ASSERT_EQ(21, d->getShape(2)->perimeter());
    delete drawing;
}

TEST_F(DBSuite, CommitNewDrawingsWithOldPainter) {
    UnitOfWork *uow = UnitOfWork::instance();

    Painter *painter = PainterMapper::instance()->find("p_0001");
    std::list<Shape *> shapes;
    shapes.push_back(new Triangle(2, 2, 2));
    Drawing *drawing = new Drawing("d_0010", painter, shapes);
    uow->registerNew(drawing);

    ASSERT_TRUE(uow->inNew("d_0010"));

    uow->commit();

    ASSERT_FALSE(uow->inNew("d_0010"));
    ASSERT_TRUE(uow->inClean("p_0001"));
    ASSERT_TRUE(uow->inClean("d_0010"));
    delete drawing;
}

// find
TEST_F(DBSuite, findDrawing) {
    Drawing * drawing = dm->find("d_0001");

    EXPECT_TRUE(UnitOfWork::instance()->inClean("d_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("d_0001"));
    EXPECT_TRUE(UnitOfWork::instance()->inClean("p_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("p_0001"));
    ASSERT_EQ(drawing->id(), "d_0001");
    ASSERT_EQ(drawing->getShape(0)->perimeter(), 3);
    ASSERT_EQ(drawing->painter()->id(), "p_0001");
    ASSERT_EQ(drawing->painter()->name(), "Patrick");
}

// can't test db, find will find in Mapper
TEST_F(DBSuite, findDrawingAndUpdate) {
    Drawing *drawing = dm->find("d_0001");
    Painter *painter = pm->find("p_0002");

    drawing->setPainter(painter);
    EXPECT_FALSE(UnitOfWork::instance()->inClean("d_0001"));
    EXPECT_TRUE(UnitOfWork::instance()->inDirty("d_0001"));
    UnitOfWork::instance()->commit();
    EXPECT_TRUE(UnitOfWork::instance()->inClean("d_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("d_0001"));

    dm->cleanCache();
    Drawing *d = dm->find("d_0001");
    EXPECT_TRUE(UnitOfWork::instance()->inClean("d_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("d_0001"));
    ASSERT_EQ("Mary", d->painter()->name());
}

TEST_F(DBSuite, findPainterAndUpdate) {
    Painter *painter = pm->find("p_0002");

    painter->setName("Mary2");
    EXPECT_FALSE(UnitOfWork::instance()->inClean("p_0002"));
    EXPECT_TRUE(UnitOfWork::instance()->inDirty("p_0002"));
    UnitOfWork::instance()->commit();
    EXPECT_TRUE(UnitOfWork::instance()->inClean("p_0002"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("p_0002"));
    pm->cleanCache();

    Painter *p = pm->find("p_0002");
    EXPECT_TRUE(UnitOfWork::instance()->inClean("p_0002"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("p_0002"));
    ASSERT_EQ("Mary2", p->name());
}

TEST_F(DBSuite, DeletePainterInNewWithoutCommit) {

    UnitOfWork *uow = UnitOfWork::instance();

    Painter *p = new Painter("p_0105", "Roy");
    uow->registerNew(p);
    ASSERT_TRUE(UnitOfWork::instance()->inNew(p->id()));
    ASSERT_FALSE(UnitOfWork::instance()->inDirty(p->id()));
    ASSERT_FALSE(UnitOfWork::instance()->inClean(p->id()));

    uow->registerDeleted(p);
    ASSERT_FALSE(UnitOfWork::instance()->inNew(p->id()));
    ASSERT_FALSE(UnitOfWork::instance()->inDirty(p->id()));
    ASSERT_FALSE(UnitOfWork::instance()->inClean(p->id()));
}

TEST_F(DBSuite, DeletePainterInClean) {
    Painter *painter = pm->find("p_0002");

    EXPECT_FALSE(UnitOfWork::instance()->inDirty(painter->id()));
    EXPECT_TRUE(UnitOfWork::instance()->inClean(painter->id()));

    UnitOfWork::instance()->registerDeleted(painter);

    EXPECT_TRUE(UnitOfWork::instance()->inDeleted(painter->id()));
    EXPECT_FALSE(UnitOfWork::instance()->inClean(painter->id()));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty(painter->id()));
    EXPECT_FALSE(UnitOfWork::instance()->inNew(painter->id()));
    UnitOfWork::instance()->commit();

    Painter *p = pm->find("p_0002");
    ASSERT_EQ(nullptr, p);
}