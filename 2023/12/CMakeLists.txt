cmake_minimum_required(VERSION 3.20)

project(2312)

Find_package(GTest)

add_executable(${PROJECT_NAME}
tests.cc
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSTIONS FALSE)

target_compile_options(${PROJECT_NAME}
  PUBLIC
  -DEXAMPLE="${CMAKE_CURRENT_SOURCE_DIR}/example"
  -DINPUT="${CMAKE_CURRENT_SOURCE_DIR}/input"
)


target_link_libraries(${PROJECT_NAME}
    GTest::GTest
    GTest::Main
    gmock
)
