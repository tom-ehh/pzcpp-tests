cmake_minimum_required(VERSION 3.22)
project(lab_06_demos LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/lab.cmake)

option(ENABLE_SANITIZERS "Build with AddressSanitizer and UBSan" OFF)
option(ENABLE_RAPIDCHECK "Download RapidCheck and build the property-based testing demo" OFF)

if(ENABLE_SANITIZERS)
  if(MSVC)
    add_compile_options(/fsanitize=address)
  else()
    add_compile_options(-fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
  endif()
endif()

add_executable(extras_demo death_test.cpp compile_time_test.cpp)
target_link_libraries(extras_demo PRIVATE GTest::gtest_main)
gtest_discover_tests(extras_demo)

add_executable(sanitizer_demo sanitizer_test.cpp)
target_link_libraries(sanitizer_demo PRIVATE GTest::gtest_main)
gtest_discover_tests(sanitizer_demo)

if(ENABLE_RAPIDCHECK)
  # RapidCheck has no releases; pin a commit.
  FetchContent_Declare(
    rapidcheck
    URL https://github.com/emil-e/rapidcheck/archive/2c3c4365aca21ef4e612768fdc95b1ce8b39a651.tar.gz
    URL_HASH SHA256=d7c87d2a728b9cd7adec09aed44f34938cd1b0928b373f9b490c5b2f6d5ab9dc
  )
  set(RC_ENABLE_GTEST ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(rapidcheck)

  add_executable(property_demo property_test.cpp)
  target_link_libraries(property_demo PRIVATE rapidcheck rapidcheck_gtest GTest::gtest_main)
  gtest_discover_tests(property_demo)
endif()
