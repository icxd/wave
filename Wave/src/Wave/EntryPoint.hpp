#pragma once

#include <Wave/Application.hpp>
#include <Wave/Log.hpp>

extern wave::Application *wave::CreateApplication();

#ifdef WAVE_PLATFORM_WINDOWS
#error Windows is not supported yet
#else
int main(int argc, char *argv[]) {
  wave::Log::Init();
  auto app = wave::CreateApplication();
  app->Run();
  delete app;
}
#endif