cmake_minimum_required(VERSION 3.12)

# Module-specific CMakeLists.txt for linalg module
# List source files in this module
set(SRC_FILES
    blas.h
    blas.c
    # Add more sources files as needed
)

# Create a library for this module
add_library(linalg_library ${SRC_FILES})

# Include directories for this module
target_include_directories(linalg_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link any additional libraries specific to this module
# We link with the math module: m.
target_link_libraries(
  linalg_library
  m
)
