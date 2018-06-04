###################################################
# Polymorphism + XML de/serialization example
###################################################

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project( serdes VERSION 0.1.0 LANGUAGES CXX )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS) # used by VS Code to setup intellisense

# ------------------------------------------------------------------------------
if(NOT TARGET boost::serialization)
  find_package(Boost REQUIRED COMPONENTS serialization)
  add_library(boost::serialization INTERFACE IMPORTED)
  set_target_properties(boost::serialization PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${Boost_INCLUDE_DIRS}"
    INTERFACE_LINK_LIBRARIES "${Boost_SERIALIZATION_LIBRARIES}")
endif()

#--------------------------------------------------------------------------------
add_definitions(-Wall)

#--------------------------------------------------------------------------------
add_executable( serdes_polymorph
  triangle.cpp
  pentagon.cpp
  main.cpp
)

target_link_libraries( serdes_polymorph 
  boost::serialization
)