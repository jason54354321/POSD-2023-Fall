#include "../src/file.h"
#include "../src/folder.h"
#include <gtest/gtest.h>

class FolderSuite : public ::testing::Test {
protected:
  Folder *folderDocument;
  Folder *folderMusic;

  void SetUp() override {
    folderDocument = new Folder("documents/111");
    folderMusic = new Folder("music/jazz");
  }

  void TearDown() override {
    delete folderDocument;
    delete folderMusic;
  }
};

TEST_F(FolderSuite, TestFolderPath) {
  ASSERT_EQ("documents/111", folderDocument->path());
  ASSERT_EQ("music/jazz", folderMusic->path());
}

TEST_F(FolderSuite, TestFolderName) {
  ASSERT_EQ("111", folderDocument->name());
  ASSERT_EQ("jazz", folderMusic->name());
}
