#include "../src/file.h"
#include "../src/folder.h"
#include <gtest/gtest.h>

class FolderIteratorSuite : public ::testing::Test {
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

// TODO: apply Iterator
TEST_F(FolderIteratorSuite, TestFolderIterator) {
  File *music1 = new File("/music/123.mp3");
  File *music2 = new File("/music/456.mp3");

  Folder *musicSubFolder = new Folder("/music/sub");

  _folderMusic->add(music1);
  _folderMusic->add(music2);
  _folderMusic->add(musicSubFolder);

  delete music1;
  delete music2;
  delete musicSubFolder;
}
