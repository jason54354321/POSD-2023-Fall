#include "ut_hello.h"
#include "ut_triangle.h"
#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
