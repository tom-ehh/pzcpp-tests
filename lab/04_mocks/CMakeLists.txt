cmake_minimum_required(VERSION 3.22)
project(lab_04_mocks LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/lab.cmake)

add_library(weather_service src/weather_service.cpp)
target_include_directories(weather_service PUBLIC src)

add_executable(weather_service_tests tests/test_weather_service.cpp)
target_link_libraries(weather_service_tests PRIVATE weather_service GTest::gmock_main)
gtest_discover_tests(weather_service_tests)
