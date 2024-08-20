#include <spdlog/common.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <wave/Log.hpp>

namespace wave {

Ref<spdlog::logger> Log::s_CoreLogger;
Ref<spdlog::logger> Log::s_ClientLogger;

void Log::Init() {
  spdlog::set_pattern("%^[%T] %n: %v%$");

  s_CoreLogger = spdlog::stdout_color_mt("WAVE");
  s_CoreLogger->set_level(spdlog::level::trace);

  s_ClientLogger = spdlog::stdout_color_mt("APP");
  s_ClientLogger->set_level(spdlog::level::trace);
}

} // namespace wave