#include "../src/file.h"
#include "../src/folder.h"
#include <gtest/gtest.h>

class FolderSuite : public ::testing::Test {
protected:
  Folder *folderDocument_;
  Folder *folderMusic_;

  void SetUp() override {
    folderDocument_ = new Folder("documents/111");
    folderMusic_ = new Folder("music/jazz");
  }

  void TearDown() override {
    delete folderDocument_;
    delete folderMusic_;
  }
};

TEST_F(FolderSuite, TestFolderPath) {
  ASSERT_EQ("documents/111", folderDocument_->path());
  ASSERT_EQ("music/jazz", folderMusic_->path());
}

TEST_F(FolderSuite, TestFolderName) {
  ASSERT_EQ("111", folderDocument_->name());
  ASSERT_EQ("jazz", folderMusic_->name());
}
