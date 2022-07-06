cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

project(main CXX)

Find_package(GTest)

add_executable(${PROJECT_NAME}
  input.cc
  main.cc
)

target_compile_options(${PROJECT_NAME}
  PUBLIC
#    -DEXAMPLE="${CMAKE_CURRENT_SOURCE_DIR}/example"
    -DINPUT="${CMAKE_CURRENT_SOURCE_DIR}/input"
    -O0
  )

target_link_libraries(${PROJECT_NAME}
  GTest::GTest
  GTest::Main
)
