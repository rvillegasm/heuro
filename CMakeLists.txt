cmake_minimum_required(VERSION 3.17)
project(heuro_cli)

set(CMAKE_CXX_STANDARD 20)

add_executable(heuro_cli main.cpp)

add_subdirectory(heuro)

target_include_directories(heuro_cli PRIVATE heuro)

target_link_libraries(heuro_cli heuro)