#include "Application.hpp"
#include "Wave/Core.hpp"
#include "Wave/Events/ApplicationEvent.hpp"
#include "Wave/Events/Event.hpp"
#include "Wave/Layer.hpp"
#include "Wave/Log.hpp"
#include "Wave/Window.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>

namespace wave {

Application *Application::s_instance = nullptr;

Application::Application() {
  s_instance = this;

  m_window = std::unique_ptr<Window>(Window::Create());
  m_window->SetEventCallback(WAVE_BIND_FN(Application::OnEvent));
}

Application::~Application() {}

void Application::Run() {
  while (m_running) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for (Layer *layer : m_layer_stack)
      layer->OnUpdate();

    m_window->OnUpdate();
  }
}

void Application::OnEvent(Event &event) {
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch<WindowCloseEvent>(
      WAVE_BIND_FN(Application::onWindowClose));

  for (auto it = m_layer_stack.end(); it != m_layer_stack.begin();) {
    (*--it)->OnEvent(event);
    if (event.Handled)
      break;
  }
}

void Application::PushLayer(Layer *layer) {
  WAVE_CORE_INFO("Pushing layer {}", layer->GetName());
  m_layer_stack.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverlay(Layer *overlay) {
  WAVE_CORE_INFO("Pushing overlay {}", overlay->GetName());
  m_layer_stack.PushOverlay(overlay);
  overlay->OnAttach();
}

bool Application::onWindowClose(WindowCloseEvent &event) {
  m_running = false;
  return true;
}

} // namespace wave