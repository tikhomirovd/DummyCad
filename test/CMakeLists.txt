# Definition is necessary to link GTest without errors
add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY=1)

add_executable(CurveTest CurveTest.cpp)
target_include_directories(CurveTest PUBLIC ${GTEST_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/../src")
target_link_libraries(CurveTest ${GTEST_BOTH_LIBRARIES} Curve)

gtest_add_tests(CurveTest "" AUTO)
