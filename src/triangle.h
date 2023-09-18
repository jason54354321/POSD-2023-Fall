#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle {
private:
  double _e1;
  double _e2;
  double _e3;

public:
  Triangle();
  Triangle(double e1, double e2, double e3) : _e1(e1), _e2(e2), _e3(e3){};
  double perimeter() {
    return _e1 + _e2 + _e3;
  }
  virtual ~Triangle();
};

#endif /* TRIANGLE_H */
