#include "../src/file.h"
#include <gtest/gtest.h>

TEST(FileSuite, TestFilePath) {
  File *file = new File("/test/123.jpg");

  file->path();
}
