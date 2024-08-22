#include <Wave.hpp>
#include <imgui.h>

using namespace wave;

class ExampleLayer : public Layer {
public:
  ExampleLayer()
      : Layer("Example"), m_camera(OrthographicCamera(-1.6f, 1.6f, -0.9, 0.9)),
        m_camera_position(0.0f) {
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

  void OnUpdate(Timestep ts) override {
    // WAVE_TRACE("delta time: {}s ({}ms)", ts.GetSeconds(),
    // ts.GetMilliseconds());

    RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    RenderCommand::Clear();

    if (Input::IsKeyPressed(KeyCode::Left))
      m_camera_position.x -= m_camera_speed * ts;
    else if (Input::IsKeyPressed(KeyCode::Right))
      m_camera_position.x += m_camera_speed * ts;

    if (Input::IsKeyPressed(KeyCode::Down))
      m_camera_position.y -= m_camera_speed * ts;
    else if (Input::IsKeyPressed(KeyCode::Up))
      m_camera_position.y += m_camera_speed * ts;

    m_camera.SetPosition(m_camera_position);

    Renderer::BeginScene(m_camera);
    Renderer::Submit(m_shader, m_vertex_array);
    Renderer::EndScene();
  }

private:
  Ref<Shader> m_shader;
  Ref<VertexArray> m_vertex_array;
  Ref<VertexBuffer> m_vertex_buffer;
  Ref<ElementBuffer> m_element_buffer;

  OrthographicCamera m_camera;
  glm::vec3 m_camera_position;
  float m_camera_speed = 1.0f;
};

class Sandbox : public Application {
public:
  Sandbox() { PushLayer(new ExampleLayer()); }
  ~Sandbox() {}
};

Application *wave::CreateApplication() { return new Sandbox(); }