cmake_minimum_required(VERSION 3.13)
project(oop_second)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest-master)

include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(oop_second  list_base.h list.h errors.h list.hpp main.cpp)
add_executable(run_test list_base.h list.h errors.h list.hpp test/test.cpp)

target_link_libraries(run_test gtest gtest_main)
