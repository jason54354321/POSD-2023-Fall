#include "hello.h"
#include <gtest/gtest.h>

TEST(HelloTest, SayHello) {
  Hello hello;
  ASSERT_EQ("hello, world", hello.sayHello("world"));
}
