#include <GLFW/glfw3.h>
#include <Wave/Core/Application.hpp>
#include <Wave/Core/Core.hpp>
#include <Wave/Core/Layer.hpp>
#include <Wave/Core/Log.hpp>
#include <Wave/Core/Window.hpp>
#include <Wave/Events/ApplicationEvent.hpp>
#include <Wave/Events/Event.hpp>
#include <Wave/Renderer/Buffer.hpp>
#include <Wave/Renderer/OrthographicCamera.hpp>
#include <Wave/Renderer/RenderCommand.hpp>
#include <Wave/Renderer/Renderer.hpp>
#include <Wave/Renderer/VertexArray.hpp>

namespace Wave {

Application *Application::s_instance = nullptr;

Application::Application() {
  s_instance = this;

  m_window = std::unique_ptr<Window>(Window::Create());
  m_window->SetEventCallback(WAVE_BIND_FN(Application::OnEvent));

  Renderer::Init();

  m_imgui_layer = new ImGuiLayer;
  PushOverlay(m_imgui_layer);
}

Application::~Application() {}

void Application::Run() {
  while (m_running) {
    float time = (float)glfwGetTime();
    Timestep timestep = time - m_last_frame_time;
    m_last_frame_time = time;

    if (!m_minimized)
      for (Layer *layer : m_layer_stack)
        layer->OnUpdate(timestep);

    m_imgui_layer->Begin();
    for (Layer *layer : m_layer_stack)
      layer->OnImGuiRender();
    m_imgui_layer->End();

    m_window->OnUpdate();
  }
}

void Application::OnEvent(Event &event) {
  EventObserver observer(event);
  observer.Observe<WindowCloseEvent>(WAVE_BIND_FN(Application::OnWindowClose));
  observer.Observe<WindowResizeEvent>(
      WAVE_BIND_FN(Application::OnWindowResize));

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

bool Application::OnWindowClose(WindowCloseEvent &event) {
  m_running = false;
  return true;
}

bool Application::OnWindowResize(WindowResizeEvent &event) {
  if (event.GetWidth() == 0 || event.GetHeight() == 0) {
    m_minimized = true;
    return true;
  }

  m_minimized = false;
  Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

  return false;
}

} // namespace Wave