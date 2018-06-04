#include "pentagon.h"

Pentagon::Pentagon(double lenght) {
  vertices = 5;
  name = "pentagon";
  this->lenght = lenght;
}

double Pentagon::area() {
  constexpr auto kAreaConst = 1.720477400588967;
  return kAreaConst * lenght * lenght;
}

void Pentagon::print() {
  std::cout << name << " (" << vertices << " vert.) -> Area: " << area() << std::endl;
}