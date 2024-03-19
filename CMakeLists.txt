cmake_minimum_required(VERSION 3.26)

project(SectorLink)

set(CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_SOURCE_DIR}/libs)

add_executable(SectorLink main.cpp)