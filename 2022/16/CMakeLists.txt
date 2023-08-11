cmake_minimum_required(VERSION 3.20)

project(2216)

Find_package(GTest)

add_executable(${PROJECT_NAME}
  main.cc
  example.cc
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

target_link_libraries(${PROJECT_NAME}
    GTest::GTest
    GTest::Main
)

  
  
