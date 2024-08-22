#pragma once

namespace wave {

enum class RendererAPI {
  None = 0,
  OpenGL = 1,
};

class Renderer {
public:
  inline static RendererAPI GetAPI() { return s_renderer_api; }

private:
  static RendererAPI s_renderer_api;
};

} // namespace wave