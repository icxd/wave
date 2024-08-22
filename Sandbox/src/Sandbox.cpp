#include <Wave.hpp>
#include <imgui.h>

using namespace wave;

class ExampleLayer : public Layer {
public:
  ExampleLayer() : Layer("Example") {}

  void OnUpdate() override {
    if (Input::IsKeyPressed(KeyCode::A))
      WAVE_INFO("A key pressed!");
  }

  void OnImGuiRender() override {
    ImGui::Begin("Test");
    ImGui::Text("Hello, world!");
    ImGui::End();
  }

  void OnEvent(Event &event) override {}
};

class Sandbox : public Application {
public:
  Sandbox() { PushLayer(new ExampleLayer()); }
  ~Sandbox() {}
};

Application *wave::CreateApplication() { return new Sandbox(); }