#pragma once

#include <Wave/Renderer/VertexArray.hpp>
#include <glm/glm.hpp>

namespace Wave {

class RendererAPI {
public:
  enum class API {
    None = 0,
    OpenGL = 1,
  };

public:
  virtual void Init() = 0;
  virtual void SetViewport(uint x, uint y, uint width, uint height) = 0;

  virtual void SetClearColor(const glm::vec4 &color) = 0;
  virtual void Clear() = 0;

  virtual void DrawElements(const Ref<VertexArray> &vertex_array) = 0;

  inline static API GetAPI() { return s_api; }

private:
  static API s_api;
};

} // namespace Wave