#include <Platform/OpenGL/OpenGLShader.hpp>
#include <Wave.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <imgui.h>
#include <memory>

using namespace wave;

class ExampleLayer : public Layer {
public:
  ExampleLayer()
      : Layer("Example"), m_camera(OrthographicCamera(-1.6f, 1.6f, -0.9, 0.9)),
        m_camera_position(0.0f) {
    m_vertex_array.reset(VertexArray::Create());

    float vertices[5 * 4] = {
        // clang-format off
      -0.5f, -0.5f, -0.0f,    0.0f, 0.0f,
       0.5f, -0.5f, -0.0f,    1.0f, 0.0f,
       0.5f,  0.5f, -0.0f,    1.0f, 1.0f,
      -0.5f,  0.5f,  0.0f,    0.0f, 1.0f,
        // clang-format on
    };

    m_vertex_buffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

    BufferLayout layout = {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float2, "a_TexCoord"},
    };

    m_vertex_buffer->SetLayout(layout);
    m_vertex_array->AddVertexBuffer(m_vertex_buffer);

    uint elements[6] = {0, 1, 2, 2, 3, 0};
    m_element_buffer.reset(
        ElementBuffer::Create(elements, sizeof(elements) / sizeof(uint)));
    m_vertex_array->SetElementBuffer(m_element_buffer);

    m_shader.reset(Shader::Create("../Sandbox/assets/shaders/simple_texture"));

    // FIXME: fix working directory
    m_texture =
        Texture2D::Create("../Sandbox/assets/textures/Checkerboard.png");
    m_cock = Texture2D::Create("../Sandbox/assets/textures/cock.png");

    std::dynamic_pointer_cast<OpenGLShader>(m_shader)->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(m_shader)->UploadUniformInt(
        "u_Texture", 0);
  }

  void OnUpdate(Timestep ts) override {
    // WAVE_TRACE("delta time: {}s ({}ms)", ts.GetSeconds(),
    // ts.GetMilliseconds());

    RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    RenderCommand::Clear();

    {
      if (Input::IsKeyPressed(KeyCode::Left))
        m_camera_position.x -= m_camera_speed * ts;
      else if (Input::IsKeyPressed(KeyCode::Right))
        m_camera_position.x += m_camera_speed * ts;

      if (Input::IsKeyPressed(KeyCode::Down))
        m_camera_position.y -= m_camera_speed * ts;
      else if (Input::IsKeyPressed(KeyCode::Up))
        m_camera_position.y += m_camera_speed * ts;

      m_camera.SetPosition(m_camera_position);
    }

    Renderer::BeginScene(m_camera);

    m_texture->Bind();
    Renderer::Submit(m_shader, m_vertex_array);

    m_cock->Bind();
    Renderer::Submit(m_shader, m_vertex_array);

    Renderer::EndScene();
  }

private:
  Ref<Shader> m_shader;
  Ref<VertexArray> m_vertex_array;
  Ref<VertexBuffer> m_vertex_buffer;
  Ref<ElementBuffer> m_element_buffer;

  Ref<Texture2D> m_texture, m_cock;

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