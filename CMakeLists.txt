cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(nested_circles)

add_executable(gen_circles src/gen_circles.cpp)
target_link_libraries(gen_circles)

add_executable(nested_circles src/nested_circles.cpp)
target_link_libraries(nested_circles)
