###################################################
# Simple De/Serialization example (with tests)
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

if(NOT TARGET catch)
  find_package(Catch REQUIRED)
  add_library(catch INTERFACE IMPORTED)
  set_target_properties(catch PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CATCH_INCLUDE_DIRS}")
endif()


#--------------------------------------------------------------------------------
add_definitions(-Wall)

#--------------------------------------------------------------------------------
add_executable( serdes_simple 
  main.cpp
)

target_link_libraries( serdes_simple 
  boost::serialization
)

# ------------------------------------------------------------------------------
# Uinit tests executable
set(TEST_NAME unittests_${PROJECT_NAME})
add_executable(${TEST_NAME}
  "unit_tests.cpp"
)
target_include_directories(${TEST_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${workspace_root}>
)
target_link_libraries(
  ${TEST_NAME}
  boost::serialization
  catch
)

# ------------------------------------------------------------------------------
# Unit tests
enable_testing()
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})