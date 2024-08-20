file(GLOB_RECURSE WAVE_SOURCES "src/*.cpp")
add_library(wave ${WAVE_SOURCES})

target_precompile_headers(wave PRIVATE "src/wavepch.h" "src/wavepch.cpp")

find_package(spdlog REQUIRED)
target_link_libraries(wave PRIVATE spdlog::spdlog)

add_compile_definitions(WAVE_BUILD_DLL WAVE_PLATFORM_LINUX)

include_directories("src/")

# install(TARGETS wave
#     LIBRARY DESTINATION lib
#     ARCHIVE DESTINATION lib)