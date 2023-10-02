#include "../src/file.h"
#include <gtest/gtest.h>

class FileSuite : public testing::Test {
protected:
  File *fileJPG_;
  File *filePNG_;
  File *fileNoExtension_;

  void SetUp() override {
    fileJPG_ = new File("/test/123.jpg");
    filePNG_ = new File("/test/456.png");
    fileNoExtension_ = new File("/test/789");
  }

  void TearDown() override {
    delete (fileJPG_);
    delete (filePNG_);
  }
};

TEST_F(FileSuite, TestFilePath) {
  ASSERT_EQ("/test/123.jpg", fileJPG_->path());
  ASSERT_EQ("/test/456.png", filePNG_->path());
  ASSERT_EQ("/test/789", fileNoExtension_->path());
}

TEST_F(FileSuite, TestFileName) {
  ASSERT_EQ("123.jpg", fileJPG_->name());
  ASSERT_EQ("456.png", filePNG_->name());
  ASSERT_EQ("789", fileNoExtension_->name());
}
