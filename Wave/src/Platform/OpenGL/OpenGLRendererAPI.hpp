#pragma once

#include <Wave/Renderer/RendererAPI.hpp>

namespace Wave {

class OpenGLRendererAPI : public RendererAPI {
public:
  virtual void Init() override;
  virtual void SetViewport(uint x, uint y, uint width, uint height) override;

  virtual void SetClearColor(const glm::vec4 &color) override;
  virtual void Clear() override;

  virtual void DrawElements(const Ref<VertexArray> &vertex_array) override;
};

} // namespace Wave