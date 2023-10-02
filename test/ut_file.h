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
  ASSERT_EQ("/test/123.jpg", _fileJPG->path());
  ASSERT_EQ("/test/456.png", _filePNG->path());
  ASSERT_EQ("/test/789", _fileNoExtension->path());
}

TEST_F(FileSuite, TestFileName) {
  ASSERT_EQ("123.jpg", _fileJPG->name());
  ASSERT_EQ("456.png", _filePNG->name());
  ASSERT_EQ("789", _fileNoExtension->name());
}
