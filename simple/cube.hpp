#pragma once

#include <boost/serialization/serialization.hpp>

class Cube {
 public:
  Cube(float width = 1, float height = 1) {
    width_ = width;
    height_ = height;
  }

  /**
   * @brief This method is used to compare loaded data from the original one. No need to implement
   * this if you don't need it.
   *
   */
  friend bool operator==(const Cube &c1, const Cube &c2) {
    return (c1.width_ == c2.width_) && (c1.height_ == c2.height_);
  }

 private:
  float width_;
  float height_;

  // Allow serialization to access non-public data members.
  friend class boost::serialization::access;
  // Implement serialize method
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar &width_ &height_;  // Simply serialize the data members
  }
};