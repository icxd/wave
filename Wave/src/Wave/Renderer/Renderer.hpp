#pragma once

#include <Wave/Renderer/Camera.hpp>
#include <Wave/Renderer/RenderCommand.hpp>
#include <Wave/Renderer/RendererAPI.hpp>
#include <Wave/Renderer/Shader.hpp>
#include <Wave/Renderer/VertexArray.hpp>

#include <glm/glm.hpp>

namespace Wave {

class Renderer {
public:
  static void Init();
  static void OnWindowResize(uint width, uint height);

  static void BeginScene(const Ref<Camera> &camera);
  static void EndScene();

  static void Submit(const Ref<Shader> &shader,
                     const Ref<VertexArray> &vertex_array,
                     const glm::mat4 &transform = glm::mat4(1.0f));

  inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

private:
  struct SceneData {
    glm::mat4 view_projection_matrix;
  };

  static SceneData *m_scene_data;
};

} // namespace Wave