# Set minimum required verison.
cmake_minimum_required(VERSION 3.12)

# Set your project's name and version
project(cmake-toolchain-howto VERSION 0.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

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

# Define the directories
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(OBJ_DIR ${CMAKE_BINARY_DIR}/obj)
set(BIN_DIR ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

# Modules within inc directory
set(MODULES
  linalg
  # Add more modules here...
)

# Add subdirectories for each module.
foreach(MODULE ${MODULES})
    add_subdirectory(${SRC_DIR}/${MODULE})
endforeach()

# Namespace convention (lib::lib) denotes to CMake that this
# is an imported target. Read up on CMake add_library ALIAS 
# for more info.
add_library(linalg::linalg ALIAS linalg_library)

# Create the output directories
file(MAKE_DIRECTORY ${OBJ_DIR})
file(MAKE_DIRECTORY ${BIN_DIR})

# Build the main executable
add_executable(main ${SRC_DIR}/main.c)

# Include directories for main
# $<BUILD_INTERFACE:...> is a generator expression to specify include
# directories that should be used when the target is built from its source.
# this effectively means that this directory (src/linalg) will not be included
# in the target's (main) interface when the target is installed and imported by
# another project. Because main should have no "consumers" including it to get
# access to the linalg module, we use this generator expression to maintain
# clear separation.
target_include_directories(
  main
  PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/linalg>
  # Add more include directories here...
)

# Link libraries as needed.
target_link_libraries(
  main
  PRIVATE
  linalg::linalg
  # Add more libraries here...
)

# If you need the objdump to be always generated when you build,
# even if my_app hasn't changed, use a custom target instead.
add_custom_target(main_objdump ALL
  DEPENDS main
  COMMAND ${CMAKE_COMMAND} -E make_directory ${OBJ_DIR}
  COMMAND ${CMAKE_OBJDUMP} -d $<TARGET_FILE:main> > ${OBJ_DIR}/main_objdump.txt
  COMMENT "Generating objdump for main"
)
