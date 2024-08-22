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

Application::Application() : m_camera(-1.9f, 1.9f, -0.9f, 0.9f) {
  s_instance = this;

  m_window = std::unique_ptr<Window>(Window::Create());
  m_window->SetEventCallback(WAVE_BIND_FN(Application::OnEvent));

  m_imgui_layer = new ImGuiLayer;
  PushOverlay(m_imgui_layer);

  m_vertex_array.reset(VertexArray::Create());

  float vertices[3 * 3] = {-0.5f, -0.5f, -0.0, 0.5f, -0.5f,
                           -0.0,  0.0f,  0.5f, -0.0};

  m_vertex_buffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

  BufferLayout layout = {
      {ShaderDataType::Float3, "a_Position"},
  };

  m_vertex_buffer->SetLayout(layout);
  m_vertex_array->AddVertexBuffer(m_vertex_buffer);

  uint elements[3] = {0, 1, 2};
  m_element_buffer.reset(
      ElementBuffer::Create(elements, sizeof(elements) / sizeof(uint)));
  m_vertex_array->SetElementBuffer(m_element_buffer);

  std::string vertex_source = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;

out vec3 v_Position;

void main() {
  v_Position = a_Position;
  gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}
  )";
  std::string fragment_source = R"(
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;

void main() {
  color = vec4(v_Position * 0.5 + 0.5, 1.0);
}
  )";

  m_shader.reset(new Shader(vertex_source, fragment_source));
}

Application::~Application() {}

void Application::Run() {
  while (m_running) {
    RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    RenderCommand::Clear();

    m_camera.SetPosition({0.5f, 0.5f, 0.0f});
    m_camera.SetRotation(45.0f);

    Renderer::BeginScene(m_camera);
    Renderer::Submit(m_shader, m_vertex_array);
    Renderer::EndScene();

    for (Layer *layer : m_layer_stack)
      layer->OnUpdate();

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