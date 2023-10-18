#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include <gtest/gtest.h>
#include <iostream>
#include <list>

using std::list;

class FolderOperatingSuite : public ::testing::Test {
protected:
  Folder *folderMusic_;
  File *music1_;
  File *music2_;
  File *music3_;
  Folder *musicSubFolder_;
  File *musicSubFolderMusic1_;

  void SetUp() override {
    folderMusic_ = new Folder("./music");
    music1_ = new File("./music/123.mp3");
    music2_ = new File("./music/456.mp3");
    music3_ = new File("./music/999.mp3");
    musicSubFolder_ = new Folder("./music/sub");
    musicSubFolderMusic1_ = new File("./music/sub/999.mp3");

    folderMusic_->add(music1_);
    folderMusic_->add(music2_);
    folderMusic_->add(music3_);
    folderMusic_->add(musicSubFolder_);
    musicSubFolder_->add(musicSubFolderMusic1_);
  }

  void TearDown() override {
    delete folderMusic_;
    delete music1_;
    delete music2_;
    delete music3_;
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
  ASSERT_EQ("999.mp3", it->currentItem()->name());
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
  Node *node = music1_->find("./music/123.mp3");
  ASSERT_EQ("123.mp3", node->name());

  node = music2_->find("./music/456.mp3");
  ASSERT_EQ("456.mp3", node->name());
}

TEST_F(FolderOperatingSuite, TestFindNestedFolder) {
  Node *node;

  node = folderMusic_->find("./music/sub/999.mp3");
  ASSERT_EQ("999.mp3", node->name());
}

TEST(FolderRemoveSuite, TestRemoveFile) {
  Folder *folderMusic_;
  File *music1_;
  File *music2_;
  Folder *musicSubFolder_;
  File *musicSubFolderMusic1_;

  folderMusic_ = new Folder("./music");
  music1_ = new File("./music/123.mp3");
  music2_ = new File("./music/456.mp3");
  musicSubFolder_ = new Folder("./music/sub");
  musicSubFolderMusic1_ = new File("./music/sub/999.mp3");

  folderMusic_->add(music1_);
  folderMusic_->add(music2_);
  folderMusic_->add(musicSubFolder_);
  musicSubFolder_->add(musicSubFolderMusic1_);

  // Remove
  folderMusic_->remove("./music/123.mp3");
  folderMusic_->remove("./music/sub/999.mp3");

  // After
  ASSERT_EQ(nullptr, folderMusic_->find("./music/123.mp3"));
  ASSERT_EQ("456.mp3", folderMusic_->find("./music/456.mp3")->name());
  ASSERT_EQ(nullptr, folderMusic_->find("./music/sub/999.mp3"));

  // clear
  delete folderMusic_;
  delete music2_;
  delete musicSubFolder_;
}

TEST(FolderRemoveSuite, TestRemoveRootFolder) {
  Folder *folderMusic_;
  Folder *musicSubFolder_;
  File *musicSubFolderMusic1_;

  folderMusic_ = new Folder("./music");
  musicSubFolder_ = new Folder("./music/sub");
  musicSubFolderMusic1_ = new File("./music/sub/999.mp3");

  folderMusic_->add(musicSubFolder_);
  musicSubFolder_->add(musicSubFolderMusic1_);

  // Remove
  folderMusic_->remove("./music/sub");

  // After
  ASSERT_EQ(nullptr, folderMusic_->find("./music/sub"));

  delete folderMusic_;
  delete musicSubFolderMusic1_;
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
  ASSERT_EQ(4, folderMusic_->numberOfFiles());
}

TEST_F(FolderOperatingSuite, TestDisabledIterator) {
  Iterator *it = folderMusic_->createIterator();

  it->first();
  ASSERT_EQ("123.mp3", it->currentItem()->name());
  it->next();
  ASSERT_EQ("456.mp3", it->currentItem()->name());

  // iterator being disabled here.
  Node *nodeAdded = new File("./music/999.mp3");
  folderMusic_->add(nodeAdded);

  ASSERT_THROW(it->next(), const char *);
}

TEST_F(FolderOperatingSuite, TestNewWithInvalidSystemPath) {
  Folder *toAdd;

  try {
    toAdd = new Folder("./toAdd");
  } catch (const char *e) {
    ASSERT_EQ("validation fail, no such file exist", e);
    return;
  }
  FAIL();
}

TEST_F(FolderOperatingSuite, FolderButWithFilePath) {
  try {
    Folder *folder = new Folder("./music/123.mp3");
  } catch (const char *e) {
    ASSERT_EQ("validation fail, no such file exist", e);
    return;
  }
  FAIL();
}

TEST_F(FolderOperatingSuite, FileButWithFolderPath) {
  try {
    File *folder = new File("./music");
  } catch (const char *e) {
    ASSERT_EQ("validation fail, no such file exist", e);
    return;
  }
  FAIL();
}

TEST_F(FolderOperatingSuite, findByName) {
  list<string> pathList = folderMusic_->findByName("999.mp3");
  ASSERT_EQ("./music/999.mp3", pathList.front());
  ASSERT_EQ("./music/sub/999.mp3", pathList.back());
}
