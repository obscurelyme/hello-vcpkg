cmake_minimum_required(VERSION 3.10)

project(Editor)

find_package(yoga CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED) # We need this because we are statically linking raylib

# FetchContent
include(FetchContent)
FetchContent_Declare(
  rlImGui
  GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
  GIT_TAG        583d4fea67e67d431319974f0625f680d3840dfb
)
FetchContent_MakeAvailable(rlImGui)
FetchContent_GetProperties(rlImGui SOURCE_DIR rlImGui_SOURCE_DIR)

set(SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/core.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/guiappbar.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/guielement.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/guipanel.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/guiroot.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/guiview.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/types.cpp"
)

set(INCLUDES
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set(TEST_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/tests/editor.cpp"
)

## Tests

enable_testing()
add_executable(EditorTests ${TEST_SOURCES} ${SOURCES} ${rlimgui_SOURCE_DIR}/rlImgui.cpp)
target_link_libraries(EditorTests PRIVATE
  raylib
  glfw 
  winmm 
  imgui::imgui
  yoga::yogacore
  GTest::gtest_main
)
target_include_directories(EditorTests PRIVATE ${INCLUDES} ${rlimgui_SOURCE_DIR})
add_compile_definitions(EditorTests PRIVATE BUILD_LIBTYPE_SHARED)
if (MSVC)
  target_compile_options(EditorTests PRIVATE /W4 /WX /utf-8)
else()
  target_compile_options(EditorTests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
include(GoogleTest)
gtest_discover_tests(EditorTests)

## Library

add_library(Editor STATIC ${SOURCES} ${rlimgui_SOURCE_DIR}/rlImgui.cpp)
target_link_libraries(Editor PRIVATE 
  imgui::imgui 
  glfw 
  winmm 
  raylib
  yoga::yogacore
)
target_include_directories(Editor PRIVATE ${rlimgui_SOURCE_DIR})
target_include_directories(Editor PUBLIC ${INCLUDES})
if (MSVC)
  target_compile_options(Editor PRIVATE /W4 /WX /utf-8)
else()
  target_compile_options(Editor PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()