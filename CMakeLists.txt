cmake_minimum_required(VERSION 3.10)
project(wave_engine CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_COMPILER clang++-18)
# set(CMAKE_CXX_STANDARD 23)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/vendor/imgui)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)
add_subdirectory(Wave)
add_subdirectory(Sandbox)