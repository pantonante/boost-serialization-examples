#include "triangle.h"

#include <iostream>

Triangle::Triangle(double base, double height) {
  vertices = 3;
  name = "triangle";
  this->base = base;
  this->height = height;
}

double Triangle::area() { return base * height / 2; }

void Triangle::print() {
  std::cout << name << " (" << vertices << " vert.) -> Area: " << area() << std::endl;
}