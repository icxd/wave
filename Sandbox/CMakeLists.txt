file(GLOB_RECURSE SANDBOX_SOURCES "src/*.cpp")
add_executable(sandbox ${SANDBOX_SOURCES})

find_package(spdlog REQUIRED)

set(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Sandbox)
message(STATUS "Working directory: ${WORKING_DIRECTORY}")

add_compile_definitions(WAVE_PLATFORM_LINUX)

include_directories(${CMAKE_SOURCE_DIR}/Wave/src)
target_link_libraries(sandbox
    PUBLIC wave
    PRIVATE spdlog::spdlog
    PRIVATE imgui)

# install(TARGETS sandbox RUNTIME DESTINATION bin)