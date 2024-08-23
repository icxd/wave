#include <Wave/Core/Log.hpp>
#include <spdlog/common.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace Wave {

Ref<spdlog::logger> Log::s_core_logger;
Ref<spdlog::logger> Log::s_client_logger;

void Log::Init() {
  spdlog::set_pattern("%^[%T] %n: %v%$");

  s_core_logger = spdlog::stdout_color_mt("WAVE");
  s_core_logger->set_level(spdlog::level::trace);

  s_client_logger = spdlog::stdout_color_mt("APP");
  s_client_logger->set_level(spdlog::level::trace);
}

} // namespace Wave