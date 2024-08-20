#pragma once

#include <memory>

#ifdef WAVE_PLATFORM_WINDOWS
#ifdef WAVE_BUILD_DLL
#define WAVE_API __declspec(dllexport)
#else // WAVE_BUILD_DLL
#define WAVE_API __declspec(dllimport)
#endif // WAVE_BUILD_DLL
#else  // WAVE_PLATFORM_WINDOWS
#define WAVE_API
#endif // WAVE_PLATFORM_WINDOWS

template <typename T> using Ref = std::shared_ptr<T>;