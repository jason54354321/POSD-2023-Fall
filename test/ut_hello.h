#include "../src/hello.h"
#include <gtest/gtest.h>

TEST(HelloTest, SayHello) {
  ASSERT_EQ("hello, world", sayHello("world"));
}
