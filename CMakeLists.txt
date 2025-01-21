cmake_minimum_required(VERSION 3.10)

project(HelloVcpkg)

# Set up C/C++ Standards
set(C_STANDARD_REQUIRED TRUE)
set(CXX_STANDARD_REQUIRED TRUE)
set(C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# Find packages
find_package(fmt CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED) # We need this because we are statically linking raylib
find_package(spdlog CONFIG REQUIRED)

# Source files
set(SOURCES
  src/main.cpp
)

# Add sources to executable
add_executable(HelloWorld ${SOURCES})

# Include directories
target_include_directories(HelloWorld PRIVATE include)

# Link libraries
target_link_libraries(HelloWorld PRIVATE fmt::fmt raylib glfw winmm spdlog::spdlog)

# Compiler options, enable all warnings
if (MSVC)
  target_compile_options(HelloWorld PRIVATE /W4 /WX)
else()
  # target_compile_options(HelloWorld PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
