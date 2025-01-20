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

# Add sources to executable
add_executable(HelloWorld hello.cpp)

# Link libraries
target_link_libraries(HelloWorld PRIVATE fmt::fmt raylib)