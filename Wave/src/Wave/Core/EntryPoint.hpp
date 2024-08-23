#pragma once

#include <Wave/Core/Application.hpp>
#include <Wave/Core/Log.hpp>

extern Wave::Application *Wave::CreateApplication();

#ifdef WAVE_PLATFORM_WINDOWS
#error Windows is not supported yet
#else
int main(int argc, char *argv[]) {
  Wave::Log::Init();
  auto app = Wave::CreateApplication();
  app->Run();
  delete app;
}
#endif