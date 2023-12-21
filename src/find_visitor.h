#pragma once

#include "triangle.h"
#include "visitor.h"
#include "compound.h"

class FindVisitor : public Visitor {
public:
    FindVisitor(double lowerBound, double upperBound) : _lowerBound(lowerBound), _upperBound(upperBound) {
    }

    void visitTriangle(Triangle * triangle) {
        if(_lowerBound <= triangle->perimeter() && _upperBound >= triangle->perimeter()) {
            _triangles.push_back(triangle);
        }
    }

    void visitCompound(Compound * compound) {
        auto it = compound->createIterator();
        for(it->first(); !it->isDone(); it->next()) {
            it->currentItem()->accept(this);
        }
    }

    std::list<Triangle *> getTriangles() const {
        return _triangles;
    }

private:
    double _lowerBound;
    double _upperBound;
    std::list<Triangle *> _triangles;
};