#pragma once

#include "iterator_factory.h"
#include "folder.h"

class FolderIteratorFactory: public IteratorFactory {
public:
    Iterator *create(Folder *folder, int operationCount) override {
        return new Folder::FolderIterator(folder, operationCount);
    }
};

class OrderByNameIteratorFactory: public IteratorFactory {
private:
    static OrderByNameIteratorFactory *_instance;
public:
    Iterator *create(Folder *folder, int operationCount) override {
        return new Folder::OrderByNameIterator(folder, operationCount);
    }

    static OrderByNameIteratorFactory *instance() {
        if (_instance == nullptr) {
            _instance = new OrderByNameIteratorFactory();
        }
        return _instance;
    }
};

class OrderByNameWithFolderFirstIteratorFactory: public IteratorFactory {
public:
    Iterator *create(Folder *folder, int operationCount) override {
        return new Folder::OrderByNameWithFolderFirstIterator(folder, operationCount);

    }
};

class OrderByKindIteratorFactory: public IteratorFactory {
public:
    Iterator *create(Folder *folder, int operationCount) override {
        return new Folder::OrderByKindIterator(folder, operationCount);
    }
};
