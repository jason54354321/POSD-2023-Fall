#pragma once

#include <string>

#include "file_system_builder.h"
#include "file_system_scanner.h"
#include "folder.h"

using std::string;

class FileSystemParser {
  private:
    FileSystemBuilder *_builder;
    FileSystemScanner *_scanner;

  public:
    FileSystemParser(FileSystemBuilder *builder) : _builder(builder) {
    }

    Folder *getRoot() const {
        return _builder->getRoot();
    }

    void parse() {
        parseHelper(_scanner, _builder);
    }

    void parseHelper(FileSystemScanner *scanner, FileSystemBuilder *builder) {
        while (1) {
            if (scanner->currentNodeName() == "." || scanner->currentNodeName() == "..") {
                scanner->nextNode();
                continue;
            }
            if (scanner->isFile()) {
                string path = scanner->pwd() + "/" + scanner->currentNodeName();
                cout << path << endl;
                builder->buildFile(path);
            } else if (scanner->isFolder()) {
                string path = scanner->pwd() + "/" + scanner->currentNodeName();
                cout << path << endl;
                builder->buildFolder(path);

                FileSystemScanner *new_scanner = new FileSystemScanner();
                new_scanner->setPath(path);
                parseHelper(new_scanner, builder);
            }

            cout << "next node" << endl;
            scanner->nextNode();

            // folder end
            if (scanner->isDone()) {
                builder->endFolder();
                break;
            }
        }
    }

    void setPath(string path) {
        _scanner = new FileSystemScanner();
        _scanner->setPath(path);
        _builder->buildFolder(path);
    }
};
