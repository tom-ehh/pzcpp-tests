cmake_minimum_required(VERSION 3.22)
project(lab_03_fixtures LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/lab.cmake)

add_library(shopping_cart src/shopping_cart.cpp)
target_include_directories(shopping_cart PUBLIC src)

add_executable(shopping_cart_tests tests/test_shopping_cart.cpp)
target_link_libraries(shopping_cart_tests PRIVATE shopping_cart GTest::gtest_main)
gtest_discover_tests(shopping_cart_tests)
