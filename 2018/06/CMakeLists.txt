cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(1806)

Find_package(GTest)
include(${CMAKE_BINARY_DIR}/Findnamedtype.cmake)

add_executable(${PROJECT_NAME}
  board.cc
  coord.cc
)

target_compile_options(${PROJECT_NAME}
  PUBLIC
    -DEXAMPLE="${CMAKE_CURRENT_SOURCE_DIR}/example"
    -DINPUT="${CMAKE_CURRENT_SOURCE_DIR}/input"
    #-O2
  )

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
  
target_link_libraries(${PROJECT_NAME}
  GTest::GTest
  GTest::Main
  structured_input
  namedtype::namedtype
)
