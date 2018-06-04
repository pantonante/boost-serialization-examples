#pragma once

#include "serialization.h"

class Polygon {
 public:
  int vertices;
  std::string name;

  virtual double area() = 0;
  virtual void print() = 0;

 private:
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar &BOOST_SERIALIZATION_NVP(name) & BOOST_SERIALIZATION_NVP(vertices);
  }
};
