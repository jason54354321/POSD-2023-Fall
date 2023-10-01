#include "../src/file.h"
#include <gtest/gtest.h>

class FileSuite : public testing::Test {
protected:
  File *_fileJPG;
  File *_filePNG;
  File *_fileNoExtension;

  void SetUp() override {
    _fileJPG = new File("/test/123.jpg");
    _filePNG = new File("/test/456.png");
    _fileNoExtension = new File("/test/789");
  }

  void TearDown() override {
    delete (_fileJPG);
    delete (_filePNG);
  }
};

TEST_F(FileSuite, TestFilePath) {
  ASSERT_EQ(_fileJPG->path(), "/test/123.jpg");
  ASSERT_EQ(_filePNG->path(), "/test/456.png");
  ASSERT_EQ(_fileNoExtension->path(), "/test/789");
}

TEST_F(FileSuite, TestFileName) {
  ASSERT_EQ(_fileJPG->name(), "123.jpg");
  ASSERT_EQ(_filePNG->name(), "456.png");
  ASSERT_EQ(_fileNoExtension->name(), "789");
}
