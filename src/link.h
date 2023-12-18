#pragma once

#include <string>
#include <list>
#include <node.h>

using namespace std;

class Link : public Node{
private:
    Node * _node;
    string _path;
    string _parent;

public:
    Link(string path): _path(path), Node(path) {
    }

    int numberOfFiles() const override {

    }

    Node * find(string path) override {

    }

    std::list<string> findByName(string name) override {

    }

    void add(Node * node) {

    }

    void remove(string path) {

    }

    Node * getChildByName(const char * name) {

    }

    void accept(Visitor * visitor) override {

    }

    Node * getTarget() {

    }
};