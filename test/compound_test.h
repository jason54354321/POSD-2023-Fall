#include "../src/compound.h"
#include "../src/shape_utils.h"
#include <vector>
#include <list>

TEST(CompoundSuite, CompoundOfTwoTriangles) {
    std::vector<Shape *> shapes = {new Triangle(1,1,1), new Triangle(2,2,2)};
    Shape * compound = new Compound(shapes);
    ASSERT_DOUBLE_EQ(9.0, compound->perimeter());
    delete compound;
}

TEST(CompoundSuite, FindTriangleWithPerimeterBetween10and20) {
    Shape * triangle = new Triangle(2, 2, 2);
    std::list<Shape *> resultShapes = find(triangle, 10, 20);
    ASSERT_EQ(0, resultShapes.size());
    delete triangle;
}

TEST(CompoundSuite, FindTriangle444WithPerimeterBetween10and20) {
    Shape * triangle = new Triangle(4, 4, 4);
    std::list<Shape *> resultShapes = find(triangle, 10, 20);
    ASSERT_EQ(1, resultShapes.size());
    delete triangle;
}

TEST(CompoundSuite, FindTriangleInCompound) {
    std::vector<Shape *> shapes = {new Triangle(1,1,1), new Triangle(5, 5, 5)};
    Shape * compound = new Compound(shapes);

    std::list<Shape *> resultShapes = find(compound, 10, 20);

    ASSERT_EQ(1, resultShapes.size());
    delete compound;
}

TEST(CompoundSuite, FindTriangleInCompoundRecursive) {
    std::vector<Shape *> shapes = {new Triangle(1,1,1), new Triangle(5, 5, 5)};
    Shape * compound = new Compound(shapes);

    std::list<Shape *> resultShapes;
    find(compound, 10, 20, resultShapes);

    ASSERT_EQ(1, resultShapes.size());
    delete compound;
}

TEST(CompoundSuite, Iterator) {
    std::vector<Shape *> shapes = {new Triangle(1,1,1), new Triangle(5, 5, 5)};
    Compound * compound = new Compound(shapes);

    ShapeIterator * it = compound->createIterator();
    
    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_DOUBLE_EQ(3.0, it->currentItem()->perimeter());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_DOUBLE_EQ(15.0, it->currentItem()->perimeter());

    it->next();
    ASSERT_TRUE(it->isDone());

    delete it;
    delete compound;
}

TEST(CompoundSuite, ToString) {
    std::vector<Shape *> shapes = {new Triangle(1,1,1), new Triangle(5, 5, 5)};
    Compound * compound = new Compound(shapes);
    ASSERT_EQ("compound { triangle 1 1 1 triangle 5 5 5 }", compound->toString());
    delete compound;
}
