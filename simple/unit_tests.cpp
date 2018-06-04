#define CATCH_CONFIG_MAIN

#include <fstream>

#include <catch.hpp>

#include "cube.hpp"
#include "map_container.hpp"
#include "vect_container.hpp"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

TEST_CASE("Vector of int", "Serialize and deserialize a vector of int") {
  VectContainer<int> vv;
  for (int n : {0, 1, 2, 3, 4, 5}) vv.elements.push_back(n);

  // Save VectContainer data to archive
  {
    std::ofstream ofs("temp.dat");
    boost::archive::text_oarchive ar(ofs);
    // Save the data
    ar &vv;
  }

  // Restore from saved data and print to verify contents
  VectContainer<int> vv_restore;
  {
    std::ifstream ifs("temp.dat");
    boost::archive::text_iarchive ar(ifs);
    // Load the data
    ar &vv_restore;
  }
  REQUIRE(vv_restore == vv);
}

TEST_CASE("Vector of custom class", "Serialize and deserialize a vector cubes") {
  VectContainer<Cube> vv;
  vv.elements.push_back(Cube(3, 5));
  vv.elements.push_back(Cube(8, 3));
  vv.elements.push_back(Cube(1, 1));

  // Save VectContainer data to archive
  {
    std::ofstream ofs("temp.dat");
    boost::archive::text_oarchive ar(ofs);
    // Save the data
    ar &vv;
  }

  // Restore from saved data and print to verify contents
  VectContainer<Cube> vv_restore;
  {
    std::ifstream ifs("temp.dat");
    boost::archive::text_iarchive ar(ifs);
    // Load the data
    ar &vv_restore;
  }
  REQUIRE(vv_restore == vv);
}

TEST_CASE("Map of (int, Custom class)", "Serialize and deserialize a map of (int, Custom class)") {
  MapContainer<int, Cube> mp;
  mp.elements[1] = Cube(3, 5);
  mp.elements[3] = Cube(3, 5);

  // Save VectContainer data to archive
  {
    std::ofstream ofs("temp.dat");
    boost::archive::text_oarchive ar(ofs);
    // Save the data
    ar &mp;
  }

  // Restore from saved data and print to verify contents
  MapContainer<int, Cube> mp_restore;
  {
    std::ifstream ifs("temp.dat");
    boost::archive::text_iarchive ar(ifs);
    // Load the data
    ar &mp_restore;
  }

  REQUIRE(mp_restore == mp);
}

TEST_CASE("Map of (int, std::vector)", "Serialize and deserialize a map of (int, std::vector)") {
  MapContainer<int, std::vector<int> > mp;
  mp.elements[1] = {1, 2, 3, 4};
  mp.elements[3] = {8, 12, 5, 7};

  // Save VectContainer data to archive
  {
    std::ofstream ofs("temp.dat");
    boost::archive::text_oarchive ar(ofs);
    // Save the data
    ar &mp;
  }

  // Restore from saved data and print to verify contents
  MapContainer<int, std::vector<int> > mp_restore;
  {
    std::ifstream ifs("temp.dat");
    boost::archive::text_iarchive ar(ifs);
    // Load the data
    ar &mp_restore;
  }

  REQUIRE(mp_restore == mp);
}