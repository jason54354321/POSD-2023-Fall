#include "../src/file.h"
#include "../src/find_by_name_visitor.h"
#include "../src/folder.h"
#include <gtest/gtest.h>

class VisitorSuite : public ::testing::Test {
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

TEST_F(VisitorSuite, findByName123) {
  Visitor *findByNameVisitor = new FindByNameVisitor("123.mp3");

  folderMusic_->accept(findByNameVisitor);
  list<string> pathList =
      dynamic_cast<FindByNameVisitor *>(findByNameVisitor)->getPathList();

  ASSERT_EQ("./music/123.mp3", pathList.front());

  delete findByNameVisitor;
}

TEST_F(VisitorSuite, findByName999) {
  Visitor *findByNameVisitor = new FindByNameVisitor("999.mp3");

  folderMusic_->accept(findByNameVisitor);
  list<string> pathList =
      dynamic_cast<FindByNameVisitor *>(findByNameVisitor)->getPathList();

  ASSERT_EQ("./music/999.mp3", pathList.front());
  ASSERT_EQ("./music/sub/999.mp3", pathList.back());

  delete findByNameVisitor;
}
