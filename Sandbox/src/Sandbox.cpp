#include <Wave.hpp>

class ExampleLayer : public wave::Layer {
public:
  ExampleLayer() : wave::Layer("Example") {}

  void OnUpdate() override { WAVE_INFO("ExampleLayer::Update"); }
  void OnEvent(wave::Event &event) override { WAVE_TRACE("{}", event); }
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