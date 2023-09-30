#include "../src/file.h"
#include <gtest/gtest.h>

TEST(FileSuite, TestFilePath) {
  File *file = new File("/test/123.jpg");

  ASSERT_EQ(file->path(), "/test/123.jpg");
}

TEST(FileSuite, TestFileName_456jpg) {
  File *file = new File("/test/456.jpg");

  ASSERT_EQ(file->name(), "456.jpg");
}

TEST(FileSuite, TestFileName_789gif) {
  File *file = new File("/test/789.gif");

  ASSERT_EQ(file->name(), "789.gif");
}

TEST(FileSuite, TestFileName_789noExtension) {
  File *file = new File("/test/789");

  ASSERT_EQ(file->name(), "789");
}

TEST(FileSuite, TestFileName_noRootBar) {
  File *file = new File("789.gif");

  ASSERT_EQ(file->name(), "789.gif");
}
