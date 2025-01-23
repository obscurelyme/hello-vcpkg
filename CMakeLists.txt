cmake_minimum_required(VERSION 3.10)

project(RaylibPong)

# Set up C/C++ Standards
set(C_STANDARD_REQUIRED TRUE)
set(CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(C_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Find packages
find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED) # We need this because we are statically linking raylib

# Source files
set(SOURCES
  src/main.cpp
)

# Add assets folder
set(ASSETS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/assets)
set(ASSETS_DEST_DIR ${CMAKE_BINARY_DIR}/assets)
add_custom_target(Assets ALL 
  COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different 
  ${ASSETS_SOURCE_DIR} ${ASSETS_DEST_DIR} 
  COMMENT "Copying assets to build directory"
)

# Add sources to executable
add_executable(RaylibPong ${SOURCES})

# Add submodules
add_subdirectory("libs/Logging")

# Include directories
target_include_directories(RaylibPong PRIVATE include)

# Link libraries
target_link_libraries(RaylibPong PRIVATE raylib glfw winmm Logging)
# add_compile_definitions(SPDLOG_COMPILED_LIB)

# Compiler options, enable all warnings
if (MSVC)
  target_compile_options(RaylibPong PRIVATE /W4 /WX /utf-8)
else()
  target_compile_options(RaylibPong PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
