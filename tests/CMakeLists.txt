cmake_minimum_required(VERSION 2.6)
project(simrec_test)

find_package(Boost 1.44 COMPONENTS unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${simrec_test_SOURCE_DIR}/..)

add_definitions(
    -DBOOST_TEST_DYN_LINK
)

file( GLOB TEST_SOURCES test.cpp sample.cpp image.cpp algorithms.cpp )
add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(run_tests Simrec ${Boost_LIBRARIES})
