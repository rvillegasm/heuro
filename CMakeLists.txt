cmake_minimum_required(VERSION 3.17)
project(heuro_cli)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "ERROR: In-source builds are not allowed!. You should create a separate directory for build files.")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_executable(heuro_cli main.cpp io/ExcelFile.cpp HeuroCli.cpp HeuroCli.hpp)

add_subdirectory(heuro)

# ----- Third party dependencies -----
add_subdirectory(vendor/xlnt)
option(STATIC "Set to ON to build xlnt as a static library instead of a shared library" ON)
option(TESTS "Set to OFF to skip building test executable (in ./tests)" OFF)
# ------------------------------------

target_include_directories(heuro_cli PRIVATE heuro vendor/xlnt/include)
target_link_libraries(heuro_cli heuro xlnt)

target_compile_definitions(heuro_cli PRIVATE HE_PROFILE)

# ----- Post build events -----
add_custom_command(
    TARGET heuro_cli
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets"
    VERBATIM
)
# -------------------------------