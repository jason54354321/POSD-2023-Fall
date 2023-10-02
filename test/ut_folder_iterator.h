#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include <gtest/gtest.h>

class FolderIteratorSuite : public ::testing::Test {
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

TEST_F(FolderIteratorSuite, TestFolderIterator) {
  File *music1 = new File("/music/123.mp3");
  File *music2 = new File("/music/456.mp3");
  Folder *musicSubFolder = new Folder("/music/sub");

  folderMusic->add(music1);
  folderMusic->add(music2);
  folderMusic->add(musicSubFolder);

  Iterator *it = folderMusic->createIterator();

  it->first();
  ASSERT_EQ("123.mp3", it->currentItem()->name());

  it->next();
  ASSERT_EQ("456.mp3", it->currentItem()->name());
  ASSERT_EQ(false, it->isDone());

  it->next();
  ASSERT_EQ("sub", it->currentItem()->name());
  ASSERT_EQ(false, it->isDone());

  it->next();
  ASSERT_EQ(true, it->isDone());

  delete music1;
  delete music2;
  delete musicSubFolder;
}
