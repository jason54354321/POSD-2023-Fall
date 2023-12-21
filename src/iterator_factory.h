#pragma once

class ShapeIterator;

class IteratorFactory {
public:
    virtual ~IteratorFactory() {}
    virtual ShapeIterator * create() = 0;
};