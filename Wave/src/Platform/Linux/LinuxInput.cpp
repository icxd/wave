#include <Platform/Linux/LinuxInput.hpp>
#include <Wave/Application.hpp>
#include <wavepch.h>

#include <GLFW/glfw3.h>

namespace Wave {

Input *Input::s_instance = new LinuxInput();

bool LinuxInput::IsKeyPressedImpl(int keycode) {
  GLFWwindow *window = static_cast<GLFWwindow *>(
      Application::Get().GetWindow().GetNativeWindow());
  int state = glfwGetKey(window, keycode);
  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool LinuxInput::IsMouseButtonPressedImpl(int button) {
  GLFWwindow *window = static_cast<GLFWwindow *>(
      Application::Get().GetWindow().GetNativeWindow());
  int state = glfwGetMouseButton(window, button);
  return state == GLFW_PRESS;
}

std::pair<float, float> LinuxInput::GetMousePosImpl() {
  GLFWwindow *window = static_cast<GLFWwindow *>(
      Application::Get().GetWindow().GetNativeWindow());
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  return {(float)xpos, (float)ypos};
}

float LinuxInput::GetMouseXImpl() {
  auto [x, y] = GetMousePosImpl();
  return x;
}

float LinuxInput::GetMouseYImpl() {
  auto [x, y] = GetMousePosImpl();
  return y;
}

} // namespace Wave