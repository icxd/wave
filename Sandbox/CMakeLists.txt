file(GLOB_RECURSE SANDBOX_SOURCES "src/*.cpp")
add_executable(sandbox ${SANDBOX_SOURCES})

add_compile_definitions(WAVE_PLATFORM_LINUX)

include_directories(${CMAKE_SOURCE_DIR}/Wave/src)
target_link_libraries(sandbox wave)

# install(TARGETS sandbox RUNTIME DESTINATION bin)