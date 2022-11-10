cmake_minimum_required(VERSION 3.22)
project(AoC2018)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
add_subdirectory(structured_input)
add_subdirectory("03 No Matter How You Slice It")
add_subdirectory("04")
add_subdirectory("05")
add_subdirectory("06")
