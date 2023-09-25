#include "../src/compound.h"
#include "../src/triangle.h"
#include <gtest/gtest.h>
#include <vector>

TEST(CompoundSuite, TestCompundInsidePerimeter) {
  Triangle *triangle1 = new Triangle(1.0, 2.0, 3.0);
  Triangle *triangle2 = new Triangle(2.0, 3.0, 4.0);
  std::vector<Shape *> shapes;
  shapes.push_back(triangle1);
  shapes.push_back(triangle2);

  Compound *compoundShape = new Compound(shapes);

  Shape *testShape1 = compoundShape->getShapes().at(0);
  Shape *testShape2 = compoundShape->getShapes().at(1);

  ASSERT_EQ(testShape1->perimeter(), 6.0);
  ASSERT_EQ(testShape2->perimeter(), 9.0);
}

TEST(CompoundSuite, TestCompundSort) {
  Triangle *triangle1 = new Triangle(9.0, 9.0, 9.0);
  Triangle *triangle2 = new Triangle(2.0, 3.0, 4.0);
  std::vector<Shape *> shapes;
  shapes.push_back(triangle1);
  shapes.push_back(triangle2);
  Compound *compoundShape = new Compound(shapes);

  compoundShape->sort();
  Shape *sortedShape1 = compoundShape->getShapes().at(0);
  Shape *sortedShape2 = compoundShape->getShapes().at(1);

  ASSERT_EQ(sortedShape1->perimeter(), 9.0);
  ASSERT_EQ(sortedShape2->perimeter(), 27.0);
}
