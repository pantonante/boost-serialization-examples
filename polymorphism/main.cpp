#include <fstream>
#include <iostream>
#include <vector>

#include "pentagon.h"
#include "polygon.h"
#include "triangle.h"

#include "archive.h"
#include "serialization.h"

void printVector(const std::vector<Polygon *> &vect) {
  for (auto it = vect.begin(); it != vect.end(); ++it) {
    (*it)->print();
  }
}

int main(int argc, char *argv[]) {
  std::vector<Polygon *> poly;
  poly.push_back(new Triangle(3, 4));
  poly.push_back(new Pentagon(5));
  poly.push_back(new Pentagon(2));
  poly.push_back(new Triangle(1, 3));

  std::cout << "# Initial vector" << std::endl;
  printVector(poly);

  std::cout << std::endl;

  std::cout << "# Serialization...";
  std::ofstream ofs("tmp.xml");
  Serializer oa(ofs);
  oa << BOOST_SERIALIZATION_NVP(poly);
  ofs.close();
  std::cout << "done." << std::endl;

  // Cleaning vector
  poly.clear();
  std::cout << std::endl;

  std::cout << "# Deserialization..." << std::endl;
  std::ifstream ifs("tmp.xml");
  Deserializer ia(ifs);
  ia >> BOOST_SERIALIZATION_NVP(poly);
  ifs.close();

  printVector(poly);

  std::cout << std::endl << "Done." << std::endl;

  return 0;
}