cmake_minimum_required(VERSION 3.22)
project(lab_02_parametrized LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/lab.cmake)

# The same PESEL code as in exercise 1.
add_library(pesel ../01_basics/src/pesel.cpp)
target_include_directories(pesel PUBLIC ../01_basics/src)

add_executable(pesel_param_tests tests/test_pesel_param.cpp)
target_link_libraries(pesel_param_tests PRIVATE pesel GTest::gtest_main)
gtest_discover_tests(pesel_param_tests)
