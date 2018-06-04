#include <fstream>
#include <iostream>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "vect_container.hpp"

int main(int argc, char **argv) {
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
    // Create and input archive
    std::ifstream ifs("temp.dat");
    boost::archive::text_iarchive ar(ifs);
    // Load the data
    ar &vv_restore;
  }

  std::cout << (vv_restore == vv) << std::endl;

  return 0;
}