#include <Wave/Core/Log.hpp>
#include <wavepch.h>

#include <Platform/OpenGL/OpenGLContext.hpp>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Wave {

void OpenGLContext::Init() {
  glfwMakeContextCurrent(m_window_handle);
  int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  WAVE_CORE_ASSERT(status, "Failed to initialize GLAD!");

  WAVE_CORE_INFO("OpenGL Information:");
  WAVE_CORE_INFO("  Vendor: {}", (const char *)glGetString(GL_VENDOR));
  WAVE_CORE_INFO("  Renderer: {}", (const char *)glGetString(GL_RENDERER));
  WAVE_CORE_INFO("  Version: {}", (const char *)glGetString(GL_VERSION));
}

void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_window_handle); }

} // namespace Wave