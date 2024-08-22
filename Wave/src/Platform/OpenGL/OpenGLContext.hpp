#pragma once

#include <Wave/Core.hpp>
#include <Wave/Log.hpp>
#include <Wave/Renderer/GraphicsContext.hpp>

#include <GLFW/glfw3.h>

namespace Wave {

class OpenGLContext : public GraphicsContext {
public:
  OpenGLContext(GLFWwindow *window_handle) : m_window_handle(window_handle) {
    WAVE_CORE_ASSERT(window_handle, "window_handle is NULL");
  }

  virtual void Init() override;
  virtual void SwapBuffers() override;

private:
  GLFWwindow *m_window_handle;
};

} // namespace Wave