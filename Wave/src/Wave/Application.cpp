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
  m_window->SetEventCallback(BIND_FN(Application::OnEvent));
}

Application::~Application() {}

void Application::Run() {
  while (m_running) {
    for (Layer *layer : m_layer_stack)
      layer->OnUpdate();

    m_window->OnUpdate();
  }
}

void Application::OnEvent(Event &event) {
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(Application::onWindowClose));

  for (auto it = m_layer_stack.end(); it != m_layer_stack.begin();) {
    (*--it)->OnEvent(event);
    if (event.Handled)
      break;
  }
}

void Application::PushLayer(Layer *layer) {
  WAVE_CORE_INFO("pushing {}", layer->GetName());
  m_layer_stack.PushLayer(layer);
  layer->OnAttach();
}

void Application::PushOverlay(Layer *overlay) {
  m_layer_stack.PushOverlay(overlay);
  overlay->OnAttach();
}

bool Application::onWindowClose(WindowCloseEvent &event) {
  m_running = false;
  return true;
}

} // namespace wave