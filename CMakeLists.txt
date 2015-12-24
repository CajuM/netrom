project(netrom)
cmake_minimum_required(VERSION 3.2)

set(CMAKE_MODULE_PATH ${CMAKE_ROOT}/Modules ${CMAKE_SOURCE_DIR}/cmake/)
include(ExternalProject)

add_subdirectory(src)
add_subdirectory(res)
