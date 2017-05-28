cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c++11)

set(NAME "mytest")
project(${NAME})
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(CMAKE_MODULE_PATH ${PROJECT_ROOT}/cmake/Modules/)

set(myThreadPool_ROOT /usr/local/myThreadPool/)
find_package(myThreadPool REQUIRED)
#set(myParallelIterator_ROOT /usr/local/myParallelIterator/)
#find_package(myParallelIterator REQUIRED)
find_package(Threads)

include_directories(${myThreadPool_INCLUDE_DIRS})
#include_directories(${myParallelIterator_INCLUDE_DIRS})
include_directories(${PROJECT_ROOT}/lib)

file(GLOB ${NAME}_HEADERS *.hpp)
file(GLOB ${NAME}_SOURCES *.cpp)

add_executable(${NAME} ${${NAME}_HEADERS} ${${NAME}_SOURCES})

target_link_libraries(${NAME} myParallelIterator)
#target_link_libraries(${NAME} ${myParallelIterator_LIBRARIES})
target_link_libraries(${NAME} ${myThreadPool_LIBRARIES})
target_link_libraries(${NAME} pthread)
