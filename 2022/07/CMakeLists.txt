cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

project(2207)

Find_package(GTest)

add_executable(${PROJECT_NAME}
  main.cc
  tree.cc
  nav.cc
)

target_compile_options(${PROJECT_NAME}
  PUBLIC
#    -DEXAMPLE="${CMAKE_CURRENT_SOURCE_DIR}/example"
    -DINPUT="${CMAKE_CURRENT_SOURCE_DIR}/input"
#    -O2
)
target_include_directories(${PROJECT_NAME}
  PUBLIC
  "/usr/include/boost/algorithm/string")

target_link_libraries(${PROJECT_NAME}
  AoC
  GTest::GTest
  GTest::Main
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
