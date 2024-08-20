#pragma once

#include <spdlog/logger.h>
#include <spdlog/spdlog.h>
#include <wave/Core.hpp>

namespace wave {

class WAVE_API Log {
public:
  static void Init();

  inline static Ref<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
  inline static Ref<spdlog::logger> &GetClientLogger() {
    return s_ClientLogger;
  }

private:
  static Ref<spdlog::logger> s_CoreLogger;
  static Ref<spdlog::logger> s_ClientLogger;
};

} // namespace wave

#define WAVE_CORE_TRACE(...) ::wave::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define WAVE_CORE_INFO(...) ::wave::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WAVE_CORE_WARN(...) ::wave::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WAVE_CORE_ERROR(...) ::wave::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WAVE_CORE_CRITICAL(...)                                                \
  ::wave::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define WAVE_TRACE(...) ::wave::Log::GetClientLogger()->trace(__VA_ARGS__)
#define WAVE_INFO(...) ::wave::Log::GetClientLogger()->info(__VA_ARGS__)
#define WAVE_WARN(...) ::wave::Log::GetClientLogger()->warn(__VA_ARGS__)
#define WAVE_ERROR(...) ::wave::Log::GetClientLogger()->error(__VA_ARGS__)
#define WAVE_CRITICAL(...) ::wave::Log::GetClientLogger()->critical(__VA_ARGS__)