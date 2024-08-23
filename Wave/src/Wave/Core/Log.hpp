#pragma once

#include <Wave/Core/Core.hpp>
#include <spdlog/fmt/ostr.h>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>

namespace Wave {

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

} // namespace Wave

#define WAVE_CORE_TRACE(...) ::Wave::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define WAVE_CORE_INFO(...) ::Wave::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WAVE_CORE_WARN(...) ::Wave::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WAVE_CORE_ERROR(...) ::Wave::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WAVE_CORE_CRITICAL(...)                                                \
  ::Wave::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define WAVE_TRACE(...) ::Wave::Log::GetClientLogger()->trace(__VA_ARGS__)
#define WAVE_INFO(...) ::Wave::Log::GetClientLogger()->info(__VA_ARGS__)
#define WAVE_WARN(...) ::Wave::Log::GetClientLogger()->warn(__VA_ARGS__)
#define WAVE_ERROR(...) ::Wave::Log::GetClientLogger()->error(__VA_ARGS__)
#define WAVE_CRITICAL(...) ::Wave::Log::GetClientLogger()->critical(__VA_ARGS__)