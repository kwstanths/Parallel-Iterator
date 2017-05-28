cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c++11)

set(LIBNAME "myParallelIterator")
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(CMAKE_MODULE_PATH ${PROJECT_ROOT}/cmake/Modules/)
project(${LIBNAME})

file(GLOB ${LIBNAME}_HEADERS *.hpp)
file(GLOB ${LIBNAME}_SOURCES *.cpp)

set(myThreadPool_ROOT /usr/local/myThreadPool/)
find_package(myThreadPool)

include_directories(${myThreadPool_INCLUDE_DIRS})

add_library(${LIBNAME} ${${LIBNAME}_HEADERS} ${${LIBNAME}_SOURCES})
set_target_properties(${LIBNAME} PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS ${LIBNAME} DESTINATION ${LIBNAME}/lib)
install(FILES ${${LIBNAME}_HEADERS} DESTINATION ${LIBNAME}/include)
