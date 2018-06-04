#pragma once

#include <boost/serialization/serialization.hpp>

#include <boost/serialization/map.hpp>

template <class K, class V>
class MapContainer {
 public:
  std::map<K, V> elements;

  /**
   * @brief This method is used to compare loaded data from the original one. No need to implement
   * this if you don't need it.
   *
   */
  friend bool operator==(const MapContainer<K, V> &m1, const MapContainer<K, V> &m2) {
    return m1.elements == m2.elements;
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