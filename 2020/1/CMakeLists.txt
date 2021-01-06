cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

project(one)

find_package(GTest)

add_executable(${PROJECT_NAME}
  main.cpp
  get_input.cpp
  solve.cpp
  )

target_link_libraries(${PROJECT_NAME}
  GTest::GTest
  GTest::Main)
