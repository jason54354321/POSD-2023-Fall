#include "iterator.h"
#include "node.h"
#include <iostream>
#include <regex>
#include <string>
#include <sys/stat.h>
#if !defined(FILE_H)
#define FILE_H

using namespace std;
class File : public Node {
private:
  string _path;

public:
  File(string path) {
    _path = path;
    struct stat sb;
    // TODO: link with OS

    if (stat("/home/jason/test", &sb) == -1) {
      perror("stat");
      exit(EXIT_FAILURE);
    }

    switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      printf("block device\n");
      break;
    case S_IFCHR:
      printf("character device\n");
      break;
    case S_IFDIR:
      printf("directory\n");
      break;
    case S_IFIFO:
      printf("FIFO/pipe\n");
      break;
    case S_IFREG:
      printf("regular file\n");
      break;
    default:
      printf("unknown?\n");
      break;
    }

    cout << "file size:" << sb.st_size << endl;
  }

  Node *find(string path) override {
    if (this->path() == path) {
      return this;
    }
    return nullptr;
  }

  string path() const override {
    return _path;
  }

  string name() const override {
    const regex regex("[^\\/]+$");
    smatch string_pieces;

    if (regex_search(_path, string_pieces, regex)) {
      return string_pieces[0];
    }
    return "Regex found no string";
  }
};

#endif // FILE_H
