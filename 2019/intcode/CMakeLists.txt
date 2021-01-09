cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

project(intcode)

add_library(intcode STATIC
  intcode.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(${PROJECT_NAME}
  PUBLIC
    #-O2
  )

project(intcode-test)
Find_package(GTest)
add_executable(${PROJECT_NAME}
  tests.cpp
  )

target_link_libraries(${PROJECT_NAME}
  GTest::GTest
  GTest::Main
  intcode)
