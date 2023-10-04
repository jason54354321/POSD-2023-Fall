#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include <gtest/gtest.h>

class FolderOperatingSuite : public ::testing::Test {
protected:
  Folder *folderDocument_;
  Folder *folderMusic_;
  File *music1_;
  File *music2_;
  Folder *musicSubFolder_;
  File *musicSubFolderMusic1_;

  void SetUp() override {
    folderDocument_ = new Folder("documents/111");

    folderMusic_ = new Folder("music");
    music1_ = new File("/music/123.mp3");
    music2_ = new File("/music/456.mp3");
    musicSubFolder_ = new Folder("/music/sub");
    musicSubFolderMusic1_ = new File("/music/sub/999.mp3");

    folderMusic_->add(music1_);
    folderMusic_->add(music2_);
    folderMusic_->add(musicSubFolder_);
    musicSubFolder_->add(musicSubFolderMusic1_);
  }

  void TearDown() override {
    delete folderDocument_;
    delete folderMusic_;
    delete music1_;
    delete music2_;
    delete musicSubFolder_;
    delete musicSubFolderMusic1_;
  }
};

TEST_F(FolderOperatingSuite, TestFolderIterator) {
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
}

TEST_F(FolderOperatingSuite, TestFindCantFind) {
  Node *node = music1_->find("/music/000.mp3");
  ASSERT_EQ(nullptr, node);
}

TEST_F(FolderOperatingSuite, TestFindFile) {
  Node *node = music1_->find("/music/123.mp3");
  ASSERT_EQ("123.mp3", node->name());

  node = music2_->find("/music/456.mp3");
  ASSERT_EQ("456.mp3", node->name());
}

TEST_F(FolderOperatingSuite, TestFindNestedFolder) {
  Node *node;

  node = folderMusic_->find("/music/sub/999.mp3");
  ASSERT_EQ("999.mp3", node->name());
}

TEST_F(FolderOperatingSuite, TestRemove) {
  // Remove
  folderMusic_->remove("/music/123.mp3");
  folderMusic_->remove("/music/sub/999.mp3");

  // After
  ASSERT_EQ(nullptr, folderMusic_->find("/music/123.mp3"));
  ASSERT_EQ("456.mp3", folderMusic_->find("/music/456.mp3")->name());
  ASSERT_EQ(nullptr, folderMusic_->find("/music/sub/999.mp3"));
}

TEST_F(FolderOperatingSuite, TestGetChildByNameNotfound) {
  ASSERT_EQ(nullptr, folderMusic_->getChildByName("000.mp3"));
}

TEST_F(FolderOperatingSuite, TestGetChildByName) {
  ASSERT_EQ("123.mp3", folderMusic_->getChildByName("123.mp3")->name());
  ASSERT_EQ("456.mp3", folderMusic_->getChildByName("456.mp3")->name());
  ASSERT_EQ("sub", folderMusic_->getChildByName("sub")->name());
}

TEST_F(FolderOperatingSuite, TestNumberOfFiles) {
  ASSERT_EQ(3, folderMusic_->numberOfFiles());
}
