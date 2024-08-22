#include "Application.hpp"
#include "Wave/Core.hpp"
#include "Wave/Events/ApplicationEvent.hpp"
#include "Wave/Events/Event.hpp"
#include "Wave/Layer.hpp"
#include "Wave/Log.hpp"
#include "Wave/Window.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <memory>

namespace wave {

Application *Application::s_instance = nullptr;

Application::Application() {
  s_instance = this;

  m_window = std::unique_ptr<Window>(Window::Create());
  m_window->SetEventCallback(WAVE_BIND_FN(Application::OnEvent));

  m_imgui_layer = new ImGuiLayer;
  PushOverlay(m_imgui_layer);

  glGenVertexArrays(1, &m_vertex_array);
  glBindVertexArray(m_vertex_array);

  glGenBuffers(1, &m_vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);

  float vertices[3 * 3] = {-0.5f, -0.5f, -0.0, 0.5f, -0.5f,
                           -0.0,  0.0f,  0.5f, -0.0};
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

  glGenBuffers(1, &m_element_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_buffer);

  uint indices[3] = {0, 1, 2};
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  std::string vertex_source = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;

out vec3 v_Position;

void main() {
  v_Position = a_Position;
  gl_Position = vec4(a_Position, 1.0);
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
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    m_shader->Bind();
    glBindVertexArray(m_vertex_array);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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