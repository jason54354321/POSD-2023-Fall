#include "../src/file.h"
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
  ASSERT_EQ("documents/111", _folderDocument->path());
  ASSERT_EQ("music/jazz", _folderMusic->path());
}

TEST_F(FolderSuite, TestFolderName) {
  ASSERT_EQ("111", _folderDocument->name());
  ASSERT_EQ("jazz", _folderMusic->name());
}
