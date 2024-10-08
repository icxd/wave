#include <Platform/OpenGL/OpenGLShader.hpp>
#include <Wave.hpp>

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <imgui.h>
#include <memory>

using namespace Wave;

class ExampleLayer : public Layer {
public:
  ExampleLayer()
      : Layer("Example"),
        m_camera_controller(CameraController(1280.0f / 720.0f)) {
    m_vertex_array.reset(VertexArray::Create());

    float vertices[5 * 4] = {
        // clang-format off
        // Vertex Pos           Texture Coord
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

    auto shader =
        m_shader_library.Load("../Sandbox/assets/shaders/simple_texture");

    // FIXME: fix working directory
    m_texture =
        Texture2D::Create("../Sandbox/assets/textures/Checkerboard.png");
    m_cock = Texture2D::Create("../Sandbox/assets/textures/cock.png");

    std::dynamic_pointer_cast<OpenGLShader>(shader)->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformInt(
        "u_Texture", 0);
  }

  void OnUpdate(Timestep ts) override {
    m_camera_controller.OnUpdate(ts);

    RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    RenderCommand::Clear();

    auto shader = m_shader_library.Get("simple_texture");

    Renderer::BeginScene(m_camera_controller.GetCamera());

    m_texture->Bind();
    Renderer::Submit(shader, m_vertex_array);

    m_cock->Bind();
    Renderer::Submit(shader, m_vertex_array);

    Renderer::EndScene();
  }

  void OnEvent(Event &event) override { m_camera_controller.OnEvent(event); }

private:
  ShaderLibrary m_shader_library;
  Ref<VertexArray> m_vertex_array;
  Ref<VertexBuffer> m_vertex_buffer;
  Ref<ElementBuffer> m_element_buffer;

  Ref<Texture2D> m_texture, m_cock;

  CameraController m_camera_controller;
};

class Sandbox : public Application {
public:
  Sandbox() { PushLayer(new ExampleLayer()); }
  ~Sandbox() {}
};

Application *Wave::CreateApplication() { return new Sandbox(); }