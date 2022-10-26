cmake_minimum_required(VERSION 3.22)

project(structured_input)

add_library(
  ${PROJECT_NAME} STATIC
  structured_input.cc)

target_include_directories(${PROJECT_NAME} PUBLIC incl)

add_subdirectory(unittest)
