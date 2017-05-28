cmake_minimum_required(VERSION 3.0)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
add_subdirectory(lib)
add_subdirectory(bin)
