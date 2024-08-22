#pragma once

namespace wave {

class GraphicsContext {
public:
  virtual void Init() = 0;
  virtual void SwapBuffers() = 0;
};

} // namespace wave