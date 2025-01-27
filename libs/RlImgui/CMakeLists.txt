cmake_minimum_required(VERSION 3.10)

project(RlImgui)

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

add_library(RlImgui STATIC ${rlimgui_SOURCE_DIR}/rlImgui.cpp)
target_link_libraries(RlImgui PRIVATE 
  imgui::imgui 
  glfw 
  winmm 
  raylib
)
target_include_directories(RlImgui INTERFACE ${rlimgui_SOURCE_DIR})