#include <wavepch.h>

#include <Platform/OpenGL/OpenGLContext.hpp>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace wave {

void OpenGLContext::Init() {
  glfwMakeContextCurrent(m_window_handle);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  WAVE_CORE_ASSERT(status, "Failed to initialize GLAD!");
}

void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_window_handle); }

} // namespace wave