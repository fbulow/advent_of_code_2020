cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

project(five)

Find_package(GTest)

add_executable(${PROJECT_NAME}
  main.cpp
  )

target_compile_options(${PROJECT_NAME}
  PUBLIC
    -Dexample="${CMAKE_CURRENT_SOURCE_DIR}/example"
    -Dinput="${CMAKE_CURRENT_SOURCE_DIR}/input"
  )

target_link_libraries(${PROJECT_NAME}
  GTest::GTest
  GTest::Main)
