#pragma once

#include <Wave/Core.hpp>
#include <spdlog/fmt/ostr.h>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>

namespace wave {

class WAVE_API Log {
public:
  static void Init();

  inline static Ref<spdlog::logger> &GetCoreLogger() { return s_core_logger; }
  inline static Ref<spdlog::logger> &GetClientLogger() {
    return s_client_logger;
  }

private:
  static Ref<spdlog::logger> s_core_logger;
  static Ref<spdlog::logger> s_client_logger;
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