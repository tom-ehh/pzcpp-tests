cmake_minimum_required(VERSION 3.22)
project(lab_03_demos LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/lab.cmake)

add_executable(lifecycle_demo lifecycle_test.cpp)
target_link_libraries(lifecycle_demo PRIVATE GTest::gtest_main)
# The whole program is one CTest test, so `ctest -V` shows its complete output.
add_test(NAME lifecycle_demo COMMAND lifecycle_demo)
