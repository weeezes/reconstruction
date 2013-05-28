cmake_minimum_required(VERSION 2.6)

add_library(Simrec image.cpp algorithms.cpp complex_array.cpp utils.cpp )
add_executable(simrec main.cpp) 
target_link_libraries(simrec Simrec) 
