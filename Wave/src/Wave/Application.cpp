#include "Application.hpp"
#include "Wave/Core.hpp"
#include "Wave/Window.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>

namespace wave {

Application::Application() {
  m_window = std::unique_ptr<Window>(Window::Create());
}

Application::~Application() {}

void Application::Run() {
  while (m_running) {
    m_window->OnUpdate();
  }
}

} // namespace wave