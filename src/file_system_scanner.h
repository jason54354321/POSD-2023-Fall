#pragma once

#include <dirent.h>
#include <iostream>
#include <string>
#include <sys/types.h>

using std::string;
using namespace std;

class FileSystemScanner {
  private:
    string _scanPath;
    DIR *dirp;
    struct dirent *dp = 0;

  public:
    bool isFile() {
        return dp->d_type == DT_REG;
    }

    bool isFolder() {
        return dp->d_type == DT_DIR;
    }

    bool isDone() {
        cout << "isDone: " << (dp == nullptr) << endl;
        return dp == nullptr;
    }

    void setPath(string path) {
        _scanPath = path;
        const char *path_c = path.c_str();
        dirp = opendir(path_c);
        dp = readdir(dirp);
    }

    string currentNodeName() {
        return dp->d_name;
    }

    string pwd() {
        return _scanPath;
    }

    void nextNode() {
        dp = readdir(dirp);
    }
};
