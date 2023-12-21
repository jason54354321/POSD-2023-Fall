#pragma once

#include <list>
#include "shape.h"
#include "triangle.h"

std::list<Shape *> find(Shape * shape, double lowerBound, double upperBound) {
    std::list<Shape *> triangles;

    if (Triangle * triangle = dynamic_cast<Triangle*>(shape)) {
        if (lowerBound <= triangle->perimeter() && upperBound >= triangle->perimeter()) {
            triangles.push_back(triangle);
        }
    }else if(Compound * compound = dynamic_cast<Compound*>(shape)) {
        auto it = compound->createIterator();
        for(it->first(); !it->isDone(); it->next()){
            if(lowerBound <= it->currentItem()->perimeter() && upperBound >= it->currentItem()->perimeter()){
                triangles.push_back(it->currentItem());
            }
        }
    }
    return triangles;
}

void find(Shape * shape, double lowerBound, double upperBound, std::list<Shape *> & triangles) {
    if (Triangle * triangle = dynamic_cast<Triangle*>(shape)) {
        if (lowerBound <= triangle->perimeter() && upperBound >= triangle->perimeter()) {
            triangles.push_back(triangle);
        }
        return;
    } else if(Compound * compound = dynamic_cast<Compound*>(shape)) {
        auto it = compound->createIterator();
        for(it->first(); !it->isDone(); it->next()){
            find(it->currentItem(), lowerBound, upperBound, triangles);
        }
    }
}