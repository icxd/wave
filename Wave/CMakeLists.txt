file(GLOB_RECURSE WAVE_SOURCES "src/*.cpp")
add_library(wave
  ${CMAKE_SOURCE_DIR}/vendor/glad/src/glad.c
  ${WAVE_SOURCES})

set(CMAKE_CXX_COMPILE_OPTIONS_USE_PCH -Winvalid-pch -x c++-header -include "src/wavepch.h")

find_package(spdlog REQUIRED)
find_package(glfw3 REQUIRED)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

target_precompile_headers(wave PRIVATE "src/wavepch.h" "src/wavepch.cpp")
target_link_libraries(wave
  PRIVATE spdlog::spdlog
  PRIVATE glfw
  PRIVATE OpenGL::GL)

add_compile_definitions(
  WAVE_BUILD_DLL 
  WAVE_PLATFORM_LINUX 
  WAVE_ENABLE_ASSERTS 
  GLFW_INCLUDE_NONE)

include_directories(
  "src/"
  "${CMAKE_SOURCE_DIR}/vendor/glad/include/")

# install(TARGETS wave
#     LIBRARY DESTINATION lib
#     ARCHIVE DESTINATION lib)