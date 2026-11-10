cmake_minimum_required(VERSION 3.22)
project(lab_01_basics LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/lab.cmake)

add_library(pesel src/pesel.cpp)
target_include_directories(pesel PUBLIC src)

# TODO (exercise 1): add the test program pesel_tests built from tests/test_pesel.cpp,
# link it with pesel and GTest::gtest_main, and register its tests in CTest.
