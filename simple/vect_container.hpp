#pragma once

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>

/**
 * @brief Create a vector containing default initialized elements
 * Note: class T, must implement operator==. This is required for testing purposes and not for
 * serialization/deserialization itself.
 *
 * @tparam T class type
 */
template <class T>
class VectContainer {
 public:
  std::vector<T> elements;  //!< we want to serialize/deserialize this vector

  /**
   * @brief This method is used to compare loaded data from the original one. No need to implement
   * this if you don't need it.
   *
   */
  friend bool operator==(const VectContainer<T> &v1, const VectContainer<T> &v2) {
    bool is_equal = false;
    if (v1.elements.size() == v2.elements.size())
      is_equal = std::equal(v2.elements.begin(), v2.elements.end(), v1.elements.begin());
    return is_equal;
  }

 private:
  // Allow serialization to access non-public data members.
  friend class boost::serialization::access;
  // Implement serialize method
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version) {
    ar &elements;
  }
};
