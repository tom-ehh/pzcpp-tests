cmake_minimum_required(VERSION 3.22)
project(lab_02_demos LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/lab.cmake)

add_executable(grade_demo grade_test.cpp)
target_link_libraries(grade_demo PRIVATE GTest::gtest_main)
gtest_discover_tests(grade_demo)
