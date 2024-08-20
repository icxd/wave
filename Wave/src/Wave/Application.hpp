#pragma once

#include <Wave/Core.hpp>
#include <Wave/Events/ApplicationEvent.hpp>
#include <Wave/Window.hpp>

namespace wave {

class WAVE_API Application {
public:
  Application();
  virtual ~Application();

  void Run();

  void OnEvent(Event &event);

private:
  bool onWindowClose(WindowCloseEvent &event);

private:
  OwnRef<Window> m_window;
  bool m_running = true;
};

Application *CreateApplication();

} // namespace wave