cmake_minimum_required(VERSION 3.10)
project(wave_engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER clang++-18)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(Wave)
add_subdirectory(Sandbox)