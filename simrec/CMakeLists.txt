cmake_minimum_required(VERSION 2.6)

add_library(Simrec image.cpp)
add_executable(simrec main.cpp) 
target_link_libraries(simrec Simrec) 
