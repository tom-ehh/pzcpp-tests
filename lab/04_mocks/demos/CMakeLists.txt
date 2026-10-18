cmake_minimum_required(VERSION 3.22)
project(lab_04_demos LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/lab.cmake)

add_executable(order_demo order_service_test.cpp)
target_link_libraries(order_demo PRIVATE GTest::gmock_main)
gtest_discover_tests(order_demo)
