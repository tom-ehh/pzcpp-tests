cmake_minimum_required(VERSION 3.22)
project(lab_01_demos LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/lab.cmake)

add_executable(float_demo float_demo.cpp)
target_link_libraries(float_demo PRIVATE GTest::gtest_main)
gtest_discover_tests(float_demo)
