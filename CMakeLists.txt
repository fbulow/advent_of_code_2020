cmake_minimum_required(VERSION 3.16.3)

project(aoc)

find_package(GTest)

add_executable(${PROJECT_NAME}
  main.cpp)

target_link_libraries(${PROJECT_NAME}
  GTest::GTest
  GTest::Main)
