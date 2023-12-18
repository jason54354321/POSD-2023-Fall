#pragma once

#include <string>
#include <list>
#include "node.h"

using namespace std;

class Link : public Node{
private:
    Node * _node;
    string _parent;

public:
    Link(string path, Node *node): _node(node), Node(path) {
        // system("cat test/ut_iterator.h");
    }

    int numberOfFiles() const override {
        _node->numberOfFiles();
    }

    Node * find(string path) override {
        return _node->find(path);
    }

    std::list<string> findByName(string name) override {
        return _node->findByName(name);
    }

    void add(Node * node) {
        _node->add(node);
    }

    void remove(string path) {
        _node->remove(path);
    }

    Node * getChildByName(const char * name) {
        return _node->getChildByName(name);
    }

    void accept(Visitor * visitor) override {
        visitor->visitLink(this);
    }

    Node * getTarget() {
        return _node;
    }
};