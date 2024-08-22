#include "Wave/Log.hpp"
#include <Platform/OpenGL/OpenGLShader.hpp>
#include <Wave.hpp>
#include <filesystem>
#include <imgui.h>
#include <memory>

class ExampleLayer : public wave::Layer {
public:
  ExampleLayer()
      : Layer("Example"),
        m_camera(wave::OrthographicCamera(-1.6f, 1.6f, -0.9, 0.9)),
        m_camera_position(0.0f) {
    m_vertex_array.reset(wave::VertexArray::Create());

    float vertices[5 * 4] = {
        // clang-format off
      -0.5f, -0.5f, -0.0f,    0.0f, 0.0f,
       0.5f, -0.5f, -0.0f,    1.0f, 0.0f,
       0.5f,  0.5f, -0.0f,    1.0f, 1.0f,
      -0.5f,  0.5f,  0.0f,    0.0f, 1.0f,
        // clang-format on
    };

    m_vertex_buffer.reset(
        wave::VertexBuffer::Create(vertices, sizeof(vertices)));

    wave::BufferLayout layout = {
        {wave::ShaderDataType::Float3, "a_Position"},
        {wave::ShaderDataType::Float2, "a_TexCoord"},
    };

    m_vertex_buffer->SetLayout(layout);
    m_vertex_array->AddVertexBuffer(m_vertex_buffer);

    uint elements[6] = {0, 1, 2, 2, 3, 0};
    m_element_buffer.reset(
        wave::ElementBuffer::Create(elements, sizeof(elements) / sizeof(uint)));
    m_vertex_array->SetElementBuffer(m_element_buffer);

    m_shader.reset(
        wave::Shader::Create("../Sandbox/assets/shaders/simple_texture"));

    std::filesystem::path path = std::filesystem::current_path();
    WAVE_INFO("Current working directory: {}", path.c_str());

    // FIXME: fix working directory
    m_texture =
        wave::Texture2D::Create("../Sandbox/assets/textures/Checkerboard.png");
    std::dynamic_pointer_cast<wave::OpenGLShader>(m_shader)->Bind();
    std::dynamic_pointer_cast<wave::OpenGLShader>(m_shader)->UploadUniformInt(
        "u_Texture", 0);
  }

  void OnUpdate(wave::Timestep ts) override {
    // WAVE_TRACE("delta time: {}s ({}ms)", ts.GetSeconds(),
    // ts.GetMilliseconds());

    wave::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    wave::RenderCommand::Clear();

    if (wave::Input::IsKeyPressed(wave::KeyCode::Left))
      m_camera_position.x -= m_camera_speed * ts;
    else if (wave::Input::IsKeyPressed(wave::KeyCode::Right))
      m_camera_position.x += m_camera_speed * ts;

    if (wave::Input::IsKeyPressed(wave::KeyCode::Down))
      m_camera_position.y -= m_camera_speed * ts;
    else if (wave::Input::IsKeyPressed(wave::KeyCode::Up))
      m_camera_position.y += m_camera_speed * ts;

    m_camera.SetPosition(m_camera_position);

    wave::Renderer::BeginScene(m_camera);

    m_texture->Bind();
    wave::Renderer::Submit(m_shader, m_vertex_array);

    wave::Renderer::EndScene();
  }

private:
  wave::Ref<wave::Shader> m_shader;
  wave::Ref<wave::VertexArray> m_vertex_array;
  wave::Ref<wave::VertexBuffer> m_vertex_buffer;
  wave::Ref<wave::ElementBuffer> m_element_buffer;
  wave::Ref<wave::Texture2D> m_texture;

  wave::OrthographicCamera m_camera;
  glm::vec3 m_camera_position;
  float m_camera_speed = 1.0f;
};

class Sandbox : public wave::Application {
public:
  Sandbox() { PushLayer(new ExampleLayer()); }
  ~Sandbox() {}
};

wave::Application *wave::CreateApplication() { return new Sandbox(); }