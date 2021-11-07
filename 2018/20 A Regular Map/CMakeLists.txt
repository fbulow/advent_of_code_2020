cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

project(201820)

Find_package(GTest)

add_executable(${PROJECT_NAME}
  tests.cpp
  position.cpp
  doors.cpp
  max_distance.cpp
  )

target_compile_options(${PROJECT_NAME}
  PUBLIC
    -DEXAMPLE="${CMAKE_CURRENT_SOURCE_DIR}/example"
    -DINPUT="${CMAKE_CURRENT_SOURCE_DIR}/input"
    #-O2
  )

target_link_libraries(${PROJECT_NAME}
  GTest::GTest
  GTest::Main)
