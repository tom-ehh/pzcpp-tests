cmake_minimum_required(VERSION 3.22)
project(lab_05_demos LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/lab.cmake)

option(ENABLE_COVERAGE "Instrument the demo for gcov/gcovr (GCC or Clang)" OFF)

add_executable(ticket_demo ticket.cpp ticket_test.cpp)
target_link_libraries(ticket_demo PRIVATE GTest::gtest_main)
if(ENABLE_COVERAGE)
  target_compile_options(ticket_demo PRIVATE --coverage -O0)
  target_link_options(ticket_demo PRIVATE --coverage)
endif()
gtest_discover_tests(ticket_demo)
