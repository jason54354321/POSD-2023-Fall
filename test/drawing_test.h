#include <gtest/gtest.h>
#include "../src/drawing.h"
#include "../src/compound.h"
#include "../src/triangle.h"
#include "../src/shape.h"
#include <list>

TEST(DrawingSuite, Drawing1) {
    std::vector<Shape *> shapes = {new Triangle(1,1,1), new Triangle(2,2,2)};
    Shape * compound = new Compound(shapes);
    Shape * t3 = new Triangle(3,3,3);
    std::list<Shape *> pics = {compound, t3};
    std::string id("d_0001");
    Painter painter("p_0001", "Patrick"); 
    DomainObject * drawing = new Drawing(id, & painter, pics);
    ASSERT_EQ("d_0001", drawing->id());
    ASSERT_EQ("Patrick", dynamic_cast<Drawing *>(drawing)->painter()->name());
    ASSERT_EQ(compound, dynamic_cast<Drawing *>(drawing)->getShape(0));
    ASSERT_EQ(t3, dynamic_cast<Drawing *>(drawing)->getShape(1));
    ASSERT_EQ("compound { triangle 1 1 1 triangle 2 2 2 }\ntriangle 3 3 3\n", dynamic_cast<Drawing *>(drawing)->getShapesAsString());

    delete drawing;
}