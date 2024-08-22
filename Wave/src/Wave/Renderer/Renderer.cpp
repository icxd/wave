#include <Platform/OpenGL/OpenGLShader.hpp>
#include <Wave/Renderer/RenderCommand.hpp>
#include <Wave/Renderer/Renderer.hpp>
#include <memory>

namespace Wave {

Renderer::SceneData *Renderer::m_scene_data = new Renderer::SceneData;

void Renderer::Init() { RenderCommand::Init(); }

void Renderer::BeginScene(PerspectiveCamera &camera) {
  m_scene_data->view_projection_matrix = camera.GetViewProjectionMatrix();
}
void Renderer::EndScene() {}

void Renderer::Submit(const Ref<Shader> &shader,
                      const Ref<VertexArray> &vertex_array,
                      const glm::mat4 &transform) {
  shader->Bind();

  std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(
      "u_ViewProjection", m_scene_data->view_projection_matrix);
  std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(
      "u_Transform", transform);

  vertex_array->Bind();
  RenderCommand::DrawElements(vertex_array);
}

} // namespace Wave