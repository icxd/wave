#include <GLFW/glfw3.h>
#include <Wave.hpp>

class ExampleLayer : public wave::Layer {
public:
  ExampleLayer() : wave::Layer("Example") {}

  void OnUpdate() override {
    if (wave::Input::IsKeyPressed(GLFW_KEY_A))
      WAVE_INFO("A key pressed!");
  }

  void OnEvent(wave::Event &event) override {}
};

class Sandbox : public wave::Application {
public:
  Sandbox() {
    PushLayer(new ExampleLayer());
    PushOverlay(new wave::ImGuiLayer);
  }
  ~Sandbox() {}
};

wave::Application *wave::CreateApplication() { return new Sandbox(); }