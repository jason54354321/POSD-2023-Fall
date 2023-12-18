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
OrderByNameIteratorFactory* OrderByNameIteratorFactory::_instance = nullptr;

class OrderByNameWithFolderFirstIteratorFactory: public IteratorFactory {
private:
    static OrderByNameWithFolderFirstIteratorFactory *_instance;
public:
    Iterator *create(Folder *folder, int operationCount) override {
        return new Folder::OrderByNameWithFolderFirstIterator(folder, operationCount);

    }

    static OrderByNameWithFolderFirstIteratorFactory *instance() {
        if (_instance == nullptr) {
            _instance = new OrderByNameWithFolderFirstIteratorFactory();
        }
        return _instance;
    }
};
OrderByNameWithFolderFirstIteratorFactory* OrderByNameWithFolderFirstIteratorFactory::_instance = nullptr;

class OrderByKindIteratorFactory: public IteratorFactory {
private:
    static OrderByKindIteratorFactory *_instance;
public:
    Iterator *create(Folder *folder, int operationCount) override {
        return new Folder::OrderByKindIterator(folder, operationCount);
    }

    static OrderByKindIteratorFactory *instance() {
        if (_instance == nullptr) {
            _instance = new OrderByKindIteratorFactory();
        }
        return _instance;
    }
};
OrderByKindIteratorFactory * OrderByKindIteratorFactory::_instance = nullptr;
