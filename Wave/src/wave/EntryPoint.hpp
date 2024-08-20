#pragma once

#include "wave/Application.hpp"
#include "wave/Log.hpp"

extern wave::Application *wave::CreateApplication();

#ifdef WAVE_PLATFORM_WINDOWS
#error Windows is not supported yet
#elifdef WAVE_PLATFORM_LINUX
int main(int argc, char *argv[]) {
  wave::Log::Init();
  auto app = wave::CreateApplication();
  app->Run();
  delete app;
}
#else
#error The platform you're on isn't supported yet.
#endif