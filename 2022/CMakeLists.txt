cmake_minimum_required(VERSION 3.20)

project(Aoc2022)
enable_testing()

add_subdirectory(AoC)
add_library(strong INTERFACE)
target_include_directories(strong INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/strong_type)


add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)

add_subdirectory(05)
add_subdirectory(06)
add_subdirectory(07)
add_subdirectory(08)
add_subdirectory(09)
add_subdirectory(10)
add_subdirectory(11)
add_subdirectory(12)
add_subdirectory(13)
add_subdirectory(14)
add_subdirectory(15)
add_subdirectory(16)

