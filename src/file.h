#include "node.h"
#include <string>
#if !defined(FILE_H)
#define FILE_H

using namespace std;
class File : public Node {
private:
  string _path;

public:
  File(string path) {
    _path = path;
  }

  string path() {
    return _path;
  }
};

#endif // FILE_H
