#ifndef COMPOUND_H
#define COMPOUND_H

#include "shape.h"
#include <algorithm>
#include <vector>

inline bool compareShape(Shape *i, Shape *j) {
  return i->perimeter() < j->perimeter();
}

class Compound {
private:
  std::vector<Shape *> shapes;

public:
  Compound(std::vector<Shape *> shapes) {
    this->shapes = shapes;
  };

	// TODO: Delete
  std::vector<Shape *> getShapes() {
    return shapes;
  }

	// TODO: double perimeter()


  void sort() {
    std::sort(shapes.begin(), shapes.end(), compareShape);
  };
};

#endif /* COMPOUND_H */
