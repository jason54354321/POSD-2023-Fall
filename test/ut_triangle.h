#include "../src/triangle.h"
#include <gtest/gtest.h>

TEST(TriangleSuite, PerimeterAdd) {
  Triangle triangle(1.0, 2.0, 3.0);

  ASSERT_EQ(triangle.perimeter(), 6);
}
