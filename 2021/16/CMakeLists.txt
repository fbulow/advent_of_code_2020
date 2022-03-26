cmake_minimum_required(VERSION 3.18)
project(packet-decoder)

Find_package(GTest)
set(CMAKE_BUILD_TYPE Debug)


add_executable(${PROJECT_NAME}
  main.cc
  impl.cc
  test.cc
  )

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  GTest::GTest
  GTest::Main
  )
