#pragma once

#include <filesystem>
#include <memory>
#include <vector>

#ifdef WAVE_PLATFORM_WINDOWS
#ifdef WAVE_BUILD_DLL
#define WAVE_API __declspec(dllexport)
#else // WAVE_BUILD_DLL
#define WAVE_API __declspec(dllimport)
#endif // WAVE_BUILD_DLL
#else  // WAVE_PLATFORM_WINDOWS
#define WAVE_API
#endif // WAVE_PLATFORM_WINDOWS

#ifdef WAVE_ENABLE_ASSERTS
#define WAVE_ASSERT(x, ...)                                                    \
  {                                                                            \
    if (!(x)) {                                                                \
      WAVE_ERROR("Assertion failed! {}", __VA_ARGS__);                         \
      raise(SIGTRAP);                                                          \
    }                                                                          \
  }
#define WAVE_CORE_ASSERT(x, ...)                                               \
  {                                                                            \
    if (!(x)) {                                                                \
      WAVE_CORE_ERROR("Assertion failed! {}", __VA_ARGS__);                    \
      raise(SIGTRAP);                                                          \
    }                                                                          \
  }
#else // WAVE_ENABLE_ASSERTS
#define WAVE_ASSERT(x, ...)
#define WAVE_CORE_ASSERT(x, ...)
#endif // WAVE_ENABLE_ASSERTS

#define WAVE_UNREACHABLE() WAVE_ASSERT(false, "Unreachable code!")
#define WAVE_CORE_UNREACHABLE() WAVE_CORE_ASSERT(false, "Unreachable code!")

#define WAVE_BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

#define BIT(x) (1 << x)

namespace Wave {

using uchar = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;

template <typename T> using Ref = std::shared_ptr<T>;
template <typename T> using Scope = std::unique_ptr<T>;
template <typename T> using Vec = std::vector<T>;

using FilePath = std::filesystem::path;

} // namespace Wave