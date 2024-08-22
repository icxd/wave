#include <Wave/Application.hpp>
#include <Wave/Core.hpp>
#include <Wave/Events/ApplicationEvent.hpp>
#include <Wave/Events/Event.hpp>
#include <Wave/Layer.hpp>
#include <Wave/Log.hpp>
#include <Wave/Renderer/Buffer.hpp>
#include <Wave/Window.hpp>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <memory>

namespace wave {

Application *Application::s_instance = nullptr;

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
  // clang-format off
  switch(type) {
  case ShaderDataType::None:   WAVE_CORE_ASSERT(false, "ShaderDataType::None is not a valid type"); return 0; 
  case ShaderDataType::Float:  return GL_FLOAT;
  case ShaderDataType::Float2: return GL_FLOAT;
  case ShaderDataType::Float3: return GL_FLOAT;
  case ShaderDataType::Float4: return GL_FLOAT;
  case ShaderDataType::Mat3:   return GL_FLOAT;
  case ShaderDataType::Mat4:   return GL_FLOAT;
  case ShaderDataType::Int:    return GL_INT;
  case ShaderDataType::Int2:   return GL_INT;
  case ShaderDataType::Int3:   return GL_INT;
  case ShaderDataType::Int4:   return GL_INT;
  case ShaderDataType::Bool:   return GL_BOOL;
  }
  // clang-format on

  WAVE_CORE_UNREACHABLE();
  return 0;
}

Application::Application() {
  s_instance = this;

  m_window = std::unique_ptr<Window>(Window::Create());
  m_window->SetEventCallback(WAVE_BIND_FN(Application::OnEvent));

  m_imgui_layer = new ImGuiLayer;
  PushOverlay(m_imgui_layer);

  glGenVertexArrays(1, &m_vertex_array);
  glBindVertexArray(m_vertex_array);

  float vertices[3 * 3] = {-0.5f, -0.5f, -0.0, 0.5f, -0.5f,
                           -0.0,  0.0f,  0.5f, -0.0};

  m_vertex_buffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

  {
    BufferLayout layout = {
        {ShaderDataType::Float3, "a_Position"},
    };

    m_vertex_buffer->SetLayout(layout);
  }

  uint index = 0;
  const auto &layout = m_vertex_buffer->GetLayout();
  for (const auto &element : layout) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, element.GetComponentCount(),
                          ShaderDataTypeToOpenGLBaseType(element.type),
                          element.normalized ? GL_TRUE : GL_FALSE,
                          layout.GetStride(), (const void *)element.offset);
    index++;
  }

  uint elements[3] = {0, 1, 2};
  m_element_buffer.reset(
      ElementBuffer::Create(elements, sizeof(elements) / sizeof(uint)));

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
    glDrawElements(GL_TRIANGLES, m_element_buffer->GetCount(), GL_UNSIGNED_INT,
                   nullptr);

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