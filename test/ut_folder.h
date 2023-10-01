#include "../src/folder.h"
#include <gtest/gtest.h>

class FolderSuite : public ::testing::Test {

protected:
  Folder *_folderDocument;
  Folder *_folderMusic;

  void SetUp() override {
    _folderDocument = new Folder("documents/111");
    _folderMusic = new Folder("music/jazz");
  }

  void TearDown() override {
    delete _folderDocument;
    delete _folderMusic;
  }
};

TEST_F(FolderSuite, TestFolderPath) {
  ASSERT_EQ(_folderDocument->path(), "documents/111");
  ASSERT_EQ(_folderMusic->path(), "music/jazz");
}

TEST_F(FolderSuite, TestFolderName) {
  ASSERT_EQ(_folderDocument->name(), "111");
  ASSERT_EQ(_folderMusic->name(), "jazz");
}
