#include "../src/dfs_iterator.h"
#include "../src/folder.h"
#include "../src/node.h"
#include <gtest/gtest.h>

class FolderDfsSuite : public ::testing::Test {
protected:
  Node *folder1_;
  Node *folder2_;
  Node *folder3_;
  Node *folder4_;
  Node *folder5_;
  Node *folder6_;
  Node *folder7_;
  Node *folder8_;

  Node *file1_;

  void SetUp() override {
    folder1_ = new Folder("/1");
    folder2_ = new Folder("/2");
    folder3_ = new Folder("/3");
    folder4_ = new Folder("/4");
    folder5_ = new Folder("/5");
    folder6_ = new Folder("/6");
    folder7_ = new Folder("/7");
    folder8_ = new Folder("/8");

    file1_ = new File("/1/file1.cpp");

    // level1
    folder1_->add(folder2_);
    folder1_->add(file1_);
    folder1_->add(folder3_);
    // level2
    folder2_->add(folder4_);
    folder2_->add(folder5_);
    folder3_->add(folder6_);
    folder3_->add(folder7_);
    // level3
    folder4_->add(folder8_);
  }

  void TearDown() override {
    delete folder1_;
    delete folder2_;
    delete folder3_;
    delete folder4_;
    delete folder5_;
    delete folder6_;
    delete folder7_;
    delete folder8_;
  }
};

TEST_F(FolderDfsSuite, TestDfsIterator) {
  Iterator *it = new DfsIterator(folder1_);

  it->first();
  ASSERT_EQ("2", it->currentItem()->name());

  it->next();
  ASSERT_EQ("4", it->currentItem()->name());
  it->next();
  ASSERT_EQ("8", it->currentItem()->name());
  it->next();
  ASSERT_EQ("5", it->currentItem()->name());
  it->next();
  ASSERT_EQ("file1.cpp", it->currentItem()->name());
  it->next();
  ASSERT_EQ("3", it->currentItem()->name());
  it->next();
  ASSERT_EQ("6", it->currentItem()->name());
  it->next();
  ASSERT_EQ("7", it->currentItem()->name());
}

TEST_F(FolderDfsSuite, TestBfsIterator) {
  Iterator *it = new BfsIterator(folder1_);

  it->first();
  ASSERT_EQ("2", it->currentItem()->name());

  it->next();
  ASSERT_EQ("file1.cpp", it->currentItem()->name());
  it->next();
  ASSERT_EQ("3", it->currentItem()->name());
  it->next();
  ASSERT_EQ("4", it->currentItem()->name());
  it->next();
  ASSERT_EQ("5", it->currentItem()->name());
  it->next();
  ASSERT_EQ("6", it->currentItem()->name());
  it->next();
  ASSERT_EQ("7", it->currentItem()->name());
  it->next();
  ASSERT_EQ("8", it->currentItem()->name());
}
