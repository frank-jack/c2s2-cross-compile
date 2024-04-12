#set minimum CMake version
cmake_minimum_required(VERSION 3.10)

#set project name and version
project(Example VERSION 1.0)

# specify the C++ standard version
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add Math subdirectory
add_subdirectory(Math)

#add executable
add_executable(Example example.cxx)

#link library to executable
target_link_libraries(Example PUBLIC Math )

#include directories
target_include_directories(Example PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Math"
                          )

#testing
enable_testing()

function(do_test test_name target arg1 arg2 result)
  add_test(NAME ${test_name} COMMAND ${target} ${arg1} ${arg2})
  set_tests_properties(${test_name}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

do_test("RootTest" Example 4 "root" "The root of 4 is 2")
do_test("SinTest" Example 1.57 "sin" "The sin of 1.57 is 1")
do_test("SquareTest" Example 5 "square" "The square of 5 is 25")
do_test("FailTest" Example 10 "x" "The x of 10 is 10")
do_test("NegativeRootTest" Example -25 "root" "The root of -25 is ")