#pragma once

#include "order_by.h"
#include "visitor.h"
#include <string>

using namespace std;

class TreeVisitor : public Visitor {
  public:
    TreeVisitor(OrderBy orderBy);

    void visitFile(File *file);
    void visitFolder(Folder *folder);

    string getTree();
};
