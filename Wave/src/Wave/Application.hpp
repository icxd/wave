#pragma once

#include <Wave/Core.hpp>
#include <Wave/Window.hpp>

namespace wave {

class WAVE_API Application {
public:
  Application();
  virtual ~Application();

  void Run();

private:
  OwnRef<Window> m_window;
  bool m_running = true;
};

Application *CreateApplication();

} // namespace wave