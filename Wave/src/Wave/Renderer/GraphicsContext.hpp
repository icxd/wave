#pragma once

namespace Wave {

class GraphicsContext {
public:
  virtual void Init() = 0;
  virtual void SwapBuffers() = 0;
};

} // namespace Wave