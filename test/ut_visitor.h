#include "../src/file.h"
#include "../src/find_by_name_visitor.h"
#include "../src/folder.h"
#include "../src/stream_out_visitor.h"
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

TEST_F(VisitorSuite, FindByName123) {
  Visitor *findByNameVisitor = new FindByNameVisitor("123.mp3");

  folderMusic_->accept(findByNameVisitor);
  list<string> pathList =
      dynamic_cast<FindByNameVisitor *>(findByNameVisitor)->getPaths();

  ASSERT_EQ("./music/123.mp3", pathList.front());

  delete findByNameVisitor;
}

TEST_F(VisitorSuite, FindByName999) {
  Visitor *findByNameVisitor = new FindByNameVisitor("999.mp3");

  folderMusic_->accept(findByNameVisitor);
  list<string> pathList =
      dynamic_cast<FindByNameVisitor *>(findByNameVisitor)->getPaths();

  ASSERT_EQ("./music/999.mp3", pathList.front());
  ASSERT_EQ("./music/sub/999.mp3", pathList.back());

  delete findByNameVisitor;
}

TEST_F(VisitorSuite, StreamOutOnFile) {
  Visitor *streamOutVisitor = new StreamOutVisitor();
  music1_->accept(streamOutVisitor);

  string out = dynamic_cast<StreamOutVisitor *>(streamOutVisitor)->getResult();
  string expectedOut = "_____________________________________________\n\
./music/123.mp3\n\
---------------------------------------------\n\
hello, world\n\
_____________________________________________\n";

  ASSERT_EQ(expectedOut, out);
}

TEST_F(VisitorSuite, StreamOutOnFolder) {
  Visitor *streamOutVisitor = new StreamOutVisitor();
  folderMusic_->accept(streamOutVisitor);

  string out = dynamic_cast<StreamOutVisitor *>(streamOutVisitor)->getResult();
  string expectedOut = "_____________________________________________\n\
./music/123.mp3\n\
---------------------------------------------\n\
hello, world\n\
_____________________________________________\n\
\n\
_____________________________________________\n\
./music/456.mp3\n\
---------------------------------------------\n\
hello, world\n\
_____________________________________________\n\
\n\
_____________________________________________\n\
./music/999.mp3\n\
---------------------------------------------\n\
hello, world\n\
_____________________________________________\n\
\n\
_____________________________________________\n\
./music/sub/999.mp3\n\
---------------------------------------------\n\
hello, world\n\
_____________________________________________\n\
\n";

  ASSERT_EQ(expectedOut, out);
}
