#include "../src/file.h"
#include "../src/folder.h"
#include <gtest/gtest.h>

class FolderBasicSuite : public ::testing::Test {
protected:
  Folder *folderDocument_;
  File *document1_;
  Folder *folderMusic_;
  File *music1_;
  File *music2_;
  Folder *musicSubFolder_;
  File *musicSubFolderMusic1_;

  void SetUp() override {
    folderDocument_ = new Folder("./documents");
    document1_ = new File("./documents/123.pdf");

    folderMusic_ = new Folder("./music");
    music1_ = new File("./music/123.mp3");
    music2_ = new File("./music/456.mp3");
    musicSubFolder_ = new Folder("./music/sub");
    musicSubFolderMusic1_ = new File("./music/sub/999.mp3");

    folderMusic_->add(music1_);
    folderMusic_->add(music2_);
    folderMusic_->add(musicSubFolder_);
    musicSubFolder_->add(musicSubFolderMusic1_);
  }

  void TearDown() override {
    delete folderDocument_;
    delete document1_;
    delete folderMusic_;
    delete music1_;
    delete music2_;
    delete musicSubFolder_;
    delete musicSubFolderMusic1_;
  }
};

TEST_F(FolderBasicSuite, TestFolderPath) {
  ASSERT_EQ("./documents", folderDocument_->path());
  ASSERT_EQ("./documents/123.pdf", document1_->path());
  ASSERT_EQ("./music", folderMusic_->path());
  ASSERT_EQ("./music/sub/999.mp3", musicSubFolderMusic1_->path());
}

TEST_F(FolderBasicSuite, TestFolderName) {
  ASSERT_EQ("documents", folderDocument_->name());
  ASSERT_EQ("123.pdf", document1_->name());
  ASSERT_EQ("music", folderMusic_->name());
  ASSERT_EQ("999.mp3", musicSubFolderMusic1_->name());
}
