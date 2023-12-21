#include "../src/shape.h"
#include "../src/triangle.h"
#include "../src/find_visitor.h"

TEST(VisitorSuite, VisitTriangle) {
    Shape * triangle = new Triangle(1, 1, 1);
    FindVisitor visitor(10, 20);

    triangle->accept(&visitor);

    ASSERT_EQ(0, visitor.getTriangles().size());

    delete triangle;
}

TEST(VisitorSuite, VisitCompound) {
    std::vector<Shape *> shapes = {new Triangle(1,1,1), new Triangle(5,5,5)};
    Shape * compound = new Compound(shapes);
    Visitor * visitor = new FindVisitor(10, 20);

    compound->accept(visitor);

    ASSERT_EQ(1, dynamic_cast<FindVisitor *>(visitor)->getTriangles().size());

    delete compound;
    delete visitor;
}

