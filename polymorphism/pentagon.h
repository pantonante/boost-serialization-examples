#pragma once

#include "polygon.h"
#include "serialization.h"

class Pentagon : public Polygon {
 public:
  Pentagon(double lenght);
  double area() override;
  virtual void print() override;

 protected:
  /**
   * @brief Boost:serialization requires a default constructor
   *
   */
  Pentagon() {}

  double lenght;

 private:
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar &BOOST_SERIALIZATION_BASE_OBJECT_NVP(Polygon) & BOOST_SERIALIZATION_NVP(lenght);
  }
};