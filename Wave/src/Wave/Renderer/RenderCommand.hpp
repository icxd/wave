#pragma once

#include <Wave/Renderer/RendererAPI.hpp>

namespace wave {

class RenderCommand {
public:
  inline static void SetClearColor(const glm::vec4 &color) {
    s_renderer_api->SetClearColor(color);
  }

  inline static void Clear() { s_renderer_api->Clear(); }

  inline static void DrawElements(const Ref<VertexArray> &vertex_array) {
    s_renderer_api->DrawElements(vertex_array);
  }

private:
  static RendererAPI *s_renderer_api;
};

} // namespace wave