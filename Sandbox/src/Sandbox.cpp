#include <Wave.hpp>

using namespace wave;

class ExampleLayer : public Layer {
public:
  ExampleLayer() : Layer("Example") {}

  void OnUpdate() override {
    if (Input::IsKeyPressed(KeyCode::A))
      WAVE_INFO("A key pressed!");
  }

  void OnEvent(Event &event) override {}
};

class Sandbox : public Application {
public:
  Sandbox() {
    PushLayer(new ExampleLayer());
    PushOverlay(new ImGuiLayer);
  }
  ~Sandbox() {}
};

Application *wave::CreateApplication() { return new Sandbox(); }