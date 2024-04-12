#set minimum CMake version
cmake_minimum_required(VERSION 3.10)

#set project name and version
project(Example VERSION 1.0)

# specify the C++ standard version
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#start of cross-comp

# Add the project root path as a compile time preprocessor definition
add_compile_definitions(PROJ_ROOT=\"${PROJECT_SOURCE_DIR}\")

# Set C flags. I append to whatever is previously set as the toolchain file
# will set CMAKE_C_FLAGS before this one. If you do not append in this case
# this command would overwrite the CMAKE_C_FLAGS that you set in the toolchain
# file.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O3 -std=c11")

# Print out some debug info to ensure we have the right flags set depending
# on the system processor we are building for.
message("CMake detected system processor: ${CMAKE_SYSTEM_PROCESSOR}")
if (CMAKE_SYSTEM_PROCESSOR STREQUAL riscv64)
  message("Cross-compiling with RISCV-GNU GCC Toolchain!")
  message("Cmake flags for riscv64: ${CMAKE_C_FLAGS}")
endif()

# Generates a compile_commands.json at the root of the build directory.
# This file is used bu IDEs and code editors to provide features for
# code completion, static analysis, and refactoring.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#end of cross-comp

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
