# Created on: April 18, 2019
# Created by: Julia Guskova
# Summary: Test curves intersection library

set(TEST_NAME "IntersectionTest")

# Definition is necessary to link GTest without errors
add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY=1)

add_executable(${TEST_NAME} IntersectionTest.cpp)
target_include_directories(${TEST_NAME} PUBLIC ${GTEST_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/../src")
target_link_libraries(${TEST_NAME} ${GTEST_BOTH_LIBRARIES} Intersection)

gtest_add_tests(${TEST_NAME} "" AUTO)
set_test_environment(${TEST_NAME})
