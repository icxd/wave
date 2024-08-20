#include "Application.hpp"
#include "Wave/Core.hpp"
#include "Wave/Events/ApplicationEvent.hpp"
#include "Wave/Events/Event.hpp"
#include "Wave/Log.hpp"
#include "Wave/Window.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>

namespace wave {

Application::Application() {
  m_window = std::unique_ptr<Window>(Window::Create());
  m_window->SetEventCallback(BIND_FN(Application::OnEvent));
}

Application::~Application() {}

void Application::Run() {
  while (m_running) {
    m_window->OnUpdate();
  }
}

void Application::OnEvent(Event &event) {
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(Application::onWindowClose));

  WAVE_CORE_TRACE("{}", event);
}

bool Application::onWindowClose(WindowCloseEvent &event) {
  m_running = false;
  return true;
}

} // namespace wave