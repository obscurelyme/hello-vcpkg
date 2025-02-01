cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_declare(
  googletest
  GIT_REPOSITORY  https://github.com/google/googletest.git
  GIT_TAG         b514bdc898e2951020cbdca1304b75f5950d1f59 # release 1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
