cmake_minimum_required(VERSION 3.20)

project(2216)

Find_package(GTest)

add_executable(${PROJECT_NAME}
  example.cc
  flood_fill.cc
  input.cc
  main.cc
  path.cc
  for_each_path.cc
  path_iteration.cc
  regions.cc
  solA.cc
  test.cc
  total_volume.cc
  types.cc
  valve_connection.cc
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSTIONS FALSE)


target_link_libraries(${PROJECT_NAME}
    GTest::GTest
    GTest::Main
)

  
  
