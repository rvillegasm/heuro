cmake_minimum_required(VERSION 3.17)
project(heuro)

set(CMAKE_CXX_STANDARD 20)

add_library(heuro Heuro.hpp Scp.cpp util/ScpParser.cpp util/Timer.cpp)
target_include_directories(heuro PRIVATE .)