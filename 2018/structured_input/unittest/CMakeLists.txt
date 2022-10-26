cmake_minimum_required(VERSION 3.22)

project(test-structured_input)

add_executable(
  ${PROJECT_NAME}
  structured_input.cc)

target_link_libraries(${PROJECT_NAME}
  gtest
  gtest_main
  structured_input

)


  
