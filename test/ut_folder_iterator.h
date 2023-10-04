#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include <gtest/gtest.h>

class FolderIteratorSuite : public ::testing::Test {
protected:
  Folder *folderDocument_;
  Folder *folderMusic_;

  void SetUp() override {
    folderDocument_ = new Folder("documents/111");
    folderMusic_ = new Folder("music");
  }

  void TearDown() override {
    delete folderDocument_;
    delete folderMusic_;
  }
};

TEST_F(FolderIteratorSuite, TestFolderIterator) {
  File *music1 = new File("/music/123.mp3");
  File *music2 = new File("/music/456.mp3");
  Folder *musicSubFolder = new Folder("/music/sub");

  folderMusic_->add(music1);
  folderMusic_->add(music2);
  folderMusic_->add(musicSubFolder);

  Iterator *it = folderMusic_->createIterator();

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

TEST_F(FolderIteratorSuite, TestFindCantFind) {
  File *music1 = new File("/music/123.mp3");

  Node *node;

  node = music1->find("/music/000.mp3");
  ASSERT_EQ(nullptr, node);

  delete music1;
}

TEST_F(FolderIteratorSuite, TestFindFile) {
  File *music1 = new File("/music/123.mp3");
  File *music2 = new File("/music/456.mp3");

  Node *node;

  node = music1->find("/music/123.mp3");
  ASSERT_EQ("123.mp3", node->name());

  node = music2->find("/music/456.mp3");
  ASSERT_EQ("456.mp3", node->name());

  delete music1;
  delete music2;
}

TEST_F(FolderIteratorSuite, TestFindNestedFolder) {
  Folder *musicSubFolder = new Folder("/music/sub");
  File *musicSubFolderMusic1 = new File("/music/sub/999.mp3");

  // top-level
  folderMusic_->add(musicSubFolder);
  // second-level
  musicSubFolder->add(musicSubFolderMusic1);

  Node *node;

  node = folderMusic_->find("/music/sub/999.mp3");
  ASSERT_EQ("999.mp3", node->name());

  delete musicSubFolder;
  delete musicSubFolderMusic1;
}

// TODO: should be composite remove
//			 had to start with find() method
TEST_F(FolderIteratorSuite, TestRemove) {
  File *music1 = new File("/music/123.mp3");
  File *music2 = new File("/music/456.mp3");
  Folder *musicSubFolder = new Folder("/music/sub");
  File *musicSubFolderMusic1 = new File("/music/sub/999.mp3");

  // top-level
  folderMusic_->add(music1);
  folderMusic_->add(music2);
  folderMusic_->add(musicSubFolder);
  // second-level
  musicSubFolder->add(musicSubFolderMusic1);

  ASSERT_EQ("999.mp3", folderMusic_->find("/music/sub/999.mp3")->name());

  // Remove
  folderMusic_->remove("/music/123.mp3");
  folderMusic_->remove("/music/sub/999.mp3");

  // After
  ASSERT_EQ(nullptr, folderMusic_->find("/music/123.mp3"));
  ASSERT_EQ("456.mp3", folderMusic_->find("/music/456.mp3")->name());
  ASSERT_EQ(nullptr, folderMusic_->find("/music/sub/999.mp3"));

  delete music1;
  delete music2;
  delete musicSubFolder;
  delete musicSubFolderMusic1;
}
