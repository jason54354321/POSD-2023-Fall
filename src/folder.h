#pragma once

#include "file.h"
#include "iterator.h"
#include "node.h"
#include "order_by.h"
#include <algorithm>
#include <iostream>
#include <list>
#include <sys/stat.h>

using namespace std;

class Folder : public Node {
  private:
    list<Node *> _nodes;
    int _operationCount = 0;

  protected:
    void removeChild(Node *target) override {
        _nodes.remove(target);
        _operationCount++;
    }

  public:
    Folder(string path) : Node(path) {
        struct stat fileInfo;
        const char *c = path.c_str();
        if (lstat(c, &fileInfo) == 0) {
            if (S_ISDIR(fileInfo.st_mode))
                return;
        }
        throw "No Folder exists";
    }

    void add(Node *node) override {
        if (node->path() != this->path() + "/" + node->name()) {
            throw string("Incorrect path of node: " + node->path());
        }
        _nodes.push_back(node);
        node->parent(this);
        _operationCount++;
    }

    Node *getChildByName(const char *name) const override {
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            if ((*it)->name() == name) {
                return *it;
            }
        }

        return nullptr;
    }

    int numberOfFiles() const override {
        int num = 0;
        if (_nodes.size() == 0) {
            return 0;
        }
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            num += (*it)->numberOfFiles();
        }
        return num;
    }

    Iterator *createIterator() override {
        return new FolderIterator(this, _operationCount);
    }

    Iterator *createIterator(OrderBy order_by) override {
        switch (order_by) {
            case OrderBy::Normal:
                return new FolderIterator(this, _operationCount);
                break;
            case OrderBy::Name:
                return new OrderByNameIterator(this, _operationCount);
                break;
            case OrderBy::NameWithFolderFirst:
                return new OrderByNameWithFolderFirstIterator(this, _operationCount);
                break;
            case OrderBy::Kind:
                return new OrderByKindIterator(this, _operationCount);
                break;
        }
    }

    Node *find(string path) override {
        if (this->path() == path) {
            return this;
        }

        size_t index = path.find(this->path());

        if (string::npos == index) {
            return nullptr;
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            Node *result = (*it)->find(path);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            std::list<string> paths = (*it)->findByName(name);
            for (auto i = paths.begin(); i != paths.end(); i++) {
                pathList.push_back(*i);
            }
        }

        return pathList;
    }

    void remove(string path) override {
        Node *target = find(path);
        if (target) {
            target->parent()->removeChild(target);
        }
    }

    void accept(Visitor *visitor) override {
        visitor->visitFolder(this);
    }

    class FolderIterator : public Iterator {
      public:
        FolderIterator(Folder *composite, int operationCount)
            : _host(composite), _operationCount(operationCount) {
        }

        ~FolderIterator() {
        }

        void first() {
            checkAvailable();
            _current = _host->_nodes.begin();
        }

        Node *currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _host->_nodes.end();
        }

      private:
        Folder *const _host;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if (_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    };

    class OrderByNameIterator : public Iterator {
      private:
        Folder *_root;
        int _operationCount;
        std::list<Node *>::iterator _current;

      public:
        OrderByNameIterator(Folder *composite, int operationCount)
            : _root(composite), _operationCount(operationCount) {
        }

        ~OrderByNameIterator() {
        }

        static bool compareByName(Node *node1, Node *node2) {
            return node1->name().at(0) < node2->name().at(0);
        }

        void first() override {
            _root->_nodes.sort(compareByName);
            _current = _root->_nodes.begin();
        }

        void next() override {
            _current++;
        }

        bool isDone() const override {
            return _current == _root->_nodes.end();
        }

        Node *currentItem() const override {
            return *(_current);
        }
    };

    class OrderByNameWithFolderFirstIterator : public Iterator {
      private:
        Folder *_root;
        int _operationCount;
        std::list<Node *>::iterator _current;

      public:
        OrderByNameWithFolderFirstIterator(Folder *composite, int operationCount)
            : _root(composite), _operationCount(operationCount) {
        }

        ~OrderByNameWithFolderFirstIterator() {
        }

        static bool compareByName(Node *node1, Node *node2) {
            return node1->name() < node2->name();
        }

        void first() override {
            // split File & Folder
            list<Node *> fileList;
            list<Node *> folderList;
            Iterator *it = _root->createIterator();
            for (it->first(); !it->isDone(); it->next()) {
                Folder *folder = dynamic_cast<Folder *>(it->currentItem());
                if (folder) {
                    folderList.push_back(folder);
                }
                File *file = dynamic_cast<File *>(it->currentItem());
                if (file) {
                    fileList.push_back(file);
                }
            }

            // sort
            folderList.sort(compareByName);
            fileList.sort(compareByName);
            // concate two list
            list<Node *> concatedList = folderList;
            concatedList.insert(concatedList.end(), fileList.begin(), fileList.end());

            // replace old list
            _root->_nodes = concatedList;
            _current = _root->_nodes.begin();
        }

        void next() override {
            _current++;
        }

        bool isDone() const override {
            return _current == _root->_nodes.end();
        }

        Node *currentItem() const override {
            return *(_current);
        }
    };

    class OrderByKindIterator : public Iterator {
      private:
        Folder *_root;
        int _operationCount;
        std::list<Node *>::iterator _current;

      public:
        OrderByKindIterator(Folder *composite, int operationCount)
            : _root(composite), _operationCount(operationCount) {
        }

        ~OrderByKindIterator() {
        }

        static bool compareByName(Node *node1, Node *node2) {
            return node1->name() < node2->name();
        }

        bool isFileHasExtension(File *file) {
            size_t index = file->name().find(".");
            if (index == string::npos) {
                return false;
            } else {
                return true;
            }
        }

        void first() override {
            // split File & Folder
            list<Node *> fileNoExtList;
            list<Node *> folderList;
            list<Node *> fileList;
            Iterator *it = _root->createIterator();
            for (it->first(); !it->isDone(); it->next()) {
                Folder *folder = dynamic_cast<Folder *>(it->currentItem());
                if (folder) {
                    folderList.push_back(folder);
                    continue;
                }
                File *file = dynamic_cast<File *>(it->currentItem());
                if (file) {
                    if (isFileHasExtension(file)) {
                        fileList.push_back(file);
                    } else {
                        fileNoExtList.push_back(file);
                    }
                    continue;
                }
            }
            // sort
            fileNoExtList.sort(compareByName);
            folderList.sort(compareByName);
            fileList.sort(compareByName);
            // concate three list
            list<Node *> concatedList = fileNoExtList;
            concatedList.insert(concatedList.end(), folderList.begin(), folderList.end());
            concatedList.insert(concatedList.end(), fileList.begin(), fileList.end());

            // replace old list
            _root->_nodes = concatedList;
            _current = _root->_nodes.begin();
        }
        void next() override {
            _current++;
        }

        bool isDone() const override {
            return _current == _root->_nodes.end();
        }

        Node *currentItem() const override {
            return *(_current);
        }
    };
};
