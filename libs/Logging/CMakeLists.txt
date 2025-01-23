cmake_minimum_required(VERSION 3.10)

project(Logging)

set(SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/core.cpp"
)

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED) # We need this because we are statically linking raylib

add_library(Logging ${SOURCES})
target_include_directories(Logging PUBLIC include)
target_link_libraries(Logging PRIVATE fmt::fmt spdlog::spdlog glfw winmm)

# Compiler options, enable all warnings
if (MSVC)
  target_compile_options(RaylibPong PRIVATE /W4 /WX /utf-8)
else()
  target_compile_options(RaylibPong PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()