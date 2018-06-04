#pragma once

#include "polygon.h"
#include "serialization.h"

class Triangle : public Polygon {
 public:
  Triangle(double base, double height);
  double area() override;
  void print();

  double base, height;

 protected:
  /**
   * @brief Boost:serialization requires a default constructor
   *
   */
  Triangle() {}

 private:
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar &BOOST_SERIALIZATION_BASE_OBJECT_NVP(Polygon) & BOOST_SERIALIZATION_NVP(base) &
        BOOST_SERIALIZATION_NVP(height);
  }
};