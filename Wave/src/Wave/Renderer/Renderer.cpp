#include <Wave/Renderer/Renderer.hpp>

namespace wave {

Renderer::SceneData *Renderer::m_scene_data = new Renderer::SceneData;

void Renderer::BeginScene(OrthographicCamera &camera) {
  m_scene_data->view_projection_matrix = camera.GetViewProjectionMatrix();
}
void Renderer::EndScene() {}

void Renderer::Submit(const Ref<Shader> &shader,
                      const Ref<VertexArray> &vertex_array) {
  shader->Bind();
  shader->UploadUniformMat4("u_ViewProjection",
                            m_scene_data->view_projection_matrix);

  vertex_array->Bind();
  RenderCommand::DrawElements(vertex_array);
}

} // namespace wave