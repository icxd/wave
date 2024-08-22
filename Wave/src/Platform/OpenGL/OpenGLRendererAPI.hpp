#pragma once

#include <Wave/Renderer/RendererAPI.hpp>

namespace wave {

class OpenGLRendererAPI : public RendererAPI {
public:
  virtual void SetClearColor(const glm::vec4 &color) override;
  virtual void Clear() override;

  virtual void DrawElements(const Ref<VertexArray> &vertex_array) override;
};

} // namespace wave