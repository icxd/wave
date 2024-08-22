#include <GLFW/glfw3.h>
#include <Wave/Application.hpp>
#include <Wave/Core.hpp>
#include <Wave/Events/ApplicationEvent.hpp>
#include <Wave/Events/Event.hpp>
#include <Wave/Layer.hpp>
#include <Wave/Log.hpp>
#include <Wave/Renderer/Buffer.hpp>
#include <Wave/Renderer/OrthographicCamera.hpp>
#include <Wave/Renderer/RenderCommand.hpp>
#include <Wave/Renderer/Renderer.hpp>
#include <Wave/Renderer/VertexArray.hpp>
#include <Wave/Window.hpp>

namespace wave {

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