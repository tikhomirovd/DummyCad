# Created on: April 15, 2019
# Created by: Artem ZHIDKOV
# Summary: Test project solving square equation

set(TEST_NAME "EquationTest")

# Definition is necessary to link GTest without errors
add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY=1)

add_executable(${TEST_NAME} EquationTest.cpp)
target_include_directories(${TEST_NAME} PUBLIC ${GTEST_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/../src")
target_link_libraries(${TEST_NAME} ${GTEST_BOTH_LIBRARIES} Equation)

gtest_add_tests(${TEST_NAME} "" AUTO)
set_test_environment(${TEST_NAME})
