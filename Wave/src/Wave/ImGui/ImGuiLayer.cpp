#include <GLFW/glfw3.h>
#include <Wave/Core/Application.hpp>
#include <Wave/Core/Core.hpp>
#include <Wave/Events/Event.hpp>
#include <Wave/Events/MouseEvent.hpp>
#include <Wave/ImGui/ImGuiLayer.hpp>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <wavepch.h>

namespace Wave {

void ImGuiLayer::OnAttach() {
  IMGUI_CHECKVERSION();
  ImGuiContext *context = ImGui::CreateContext();
  ImGui::SetCurrentContext(context);

  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  ImGui::StyleColorsDark();

  ImGuiStyle &style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  Application &app = Application::Get();
  GLFWwindow *window =
      static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDetach() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiLayer::OnImGuiRender() {}

void ImGuiLayer::Begin() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void ImGuiLayer::End() {
  ImGuiIO &io = ImGui::GetIO();
  Application &app = Application::Get();
  io.DisplaySize =
      ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow *backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}

} // namespace Wave