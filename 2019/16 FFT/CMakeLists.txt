CMAKE_MINIMUM_REQUIRED(  VERSION 3.16.3 )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(sixteen)

Find_package(GTest)

add_executable(${PROJECT_NAME}
  test.cpp
  summation.cpp
  cycle.cpp
  offset.cpp
  )

target_link_libraries(
  ${PROJECT_NAME}
  GTest::GTest
  GTest::Main)

target_compile_options(${PROJECT_NAME}
  PUBLIC
    -DINPUT="${CMAKE_CURRENT_SOURCE_DIR}/input"
  )
