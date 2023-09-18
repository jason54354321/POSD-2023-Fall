#include "../src/triangle.h"
#include <gtest/gtest.h>

TEST(HelloTest, SayHello) {
  Triangle triangle(1, 2, 3);

  ASSERT_EQ(triangle.perimeter(), 12);
}
