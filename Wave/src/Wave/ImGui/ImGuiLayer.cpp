#include <GLFW/glfw3.h>
#include <Platform/OpenGL/ImGuiOpenGLRenderer.hpp>
#include <Wave/Application.hpp>
#include <Wave/Core.hpp>
#include <Wave/Events/Event.hpp>
#include <Wave/Events/MouseEvent.hpp>
#include <Wave/ImGui/ImGuiLayer.hpp>
#include <glad/glad.h>
#include <imgui.h>
#include <wavepch.h>

namespace wave {

void ImGuiLayer::OnAttach() {
  ImGuiContext *context = ImGui::CreateContext();
  ImGui::SetCurrentContext(context);

  ImGui::StyleColorsDark();

  ImGuiIO &io = ImGui::GetIO();
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

  io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
  io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
  io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
  io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
  io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
  io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
  io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
  io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
  io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
  io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
  io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
  io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
  io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
  io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
  io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
  io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
  io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
  io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
  io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
  io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
  io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

  ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDetach() {}

void ImGuiLayer::OnUpdate() {
  ImGuiIO &io = ImGui::GetIO();
  Application &app = Application::Get();
  io.DisplaySize =
      ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

  float time = (float)glfwGetTime();
  io.DeltaTime = m_time > 0.0 ? (time - m_time) : (1.0f / 60.0f);
  m_time = time;

  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();

  static bool show = true;
  ImGui::ShowDemoWindow(&show);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event &event) {
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch<MouseButtonPressedEvent>(
      WAVE_BIND_FN(ImGuiLayer::OnMouseButtonPressedEvent));
  dispatcher.Dispatch<MouseButtonReleasedEvent>(
      WAVE_BIND_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
  dispatcher.Dispatch<MouseMovedEvent>(
      WAVE_BIND_FN(ImGuiLayer::OnMouseMovedEvent));
  dispatcher.Dispatch<MouseScrolledEvent>(
      WAVE_BIND_FN(ImGuiLayer::OnMouseScrolledEvent));
  dispatcher.Dispatch<KeyPressedEvent>(
      WAVE_BIND_FN(ImGuiLayer::OnKeyPressedEvent));
  dispatcher.Dispatch<KeyReleasedEvent>(
      WAVE_BIND_FN(ImGuiLayer::OnKeyReleasedEvent));
  dispatcher.Dispatch<KeyTypedEvent>(WAVE_BIND_FN(ImGuiLayer::OnKeyTypedEvent));
  dispatcher.Dispatch<WindowResizeEvent>(
      WAVE_BIND_FN(ImGuiLayer::OnWindowResizeEvent));
}

bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.MouseDown[event.GetMouseButton()] = true;
  return false;
}

bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.MouseDown[event.GetMouseButton()] = false;
  return false;
}

bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.MousePos = ImVec2(event.GetX(), event.GetY());
  return false;
}

bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.MouseWheelH += event.GetXOffset();
  io.MouseWheel += event.GetYOffset();
  return false;
}

bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.KeysDown[event.GetKeyCode()] = true;
  return false;
}

bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.KeysDown[event.GetKeyCode()] = false;

  io.KeyCtrl =
      io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
  io.KeyShift =
      io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
  io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
  io.KeySuper =
      io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

  return false;
}

bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent &event) {
  ImGuiIO &io = ImGui::GetIO();
  if (event.GetKeyCode() > 0 && event.GetKeyCode() < 0x10000)
    io.AddInputCharacter((uint)event.GetKeyCode());
  return false;
}

bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent &event) {
  ImGuiIO &io = ImGui::GetIO();
  io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
  io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
  glViewport(0, 0, event.GetWidth(), event.GetHeight());
  return false;
}

} // namespace wave