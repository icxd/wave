#pragma once

#include <Wave/Renderer/OrthographicCamera.hpp>
#include <Wave/Renderer/RenderCommand.hpp>
#include <Wave/Renderer/RendererAPI.hpp>
#include <Wave/Renderer/Shader.hpp>
#include <Wave/Renderer/VertexArray.hpp>

#include <glm/glm.hpp>

namespace wave {

class Renderer {
public:
  static void BeginScene(OrthographicCamera &camera);
  static void EndScene();

  static void Submit(const Ref<Shader> &shader,
                     const Ref<VertexArray> &vertex_array);

  inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

private:
  struct SceneData {
    glm::mat4 view_projection_matrix;
  };

  static SceneData *m_scene_data;
};

} // namespace wave