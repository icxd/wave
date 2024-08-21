#pragma once

#include <Wave/Core.hpp>
#include <Wave/Events/ApplicationEvent.hpp>
#include <Wave/Events/Event.hpp>
#include <Wave/Events/KeyEvent.hpp>
#include <Wave/Events/MouseEvent.hpp>
#include <Wave/Layer.hpp>

namespace wave {

class WAVE_API ImGuiLayer : public Layer {
public:
  ImGuiLayer() : Layer("ImGuiLayer") {}
  ~ImGuiLayer() = default;

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate() override;
  void OnEvent(Event &event) override;

private:
  bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &event);
  bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event);
  bool OnMouseMovedEvent(MouseMovedEvent &event);
  bool OnMouseScrolledEvent(MouseScrolledEvent &event);
  bool OnKeyPressedEvent(KeyPressedEvent &event);
  bool OnKeyReleasedEvent(KeyReleasedEvent &event);
  bool OnKeyTypedEvent(KeyTypedEvent &event);
  bool OnWindowResizeEvent(WindowResizeEvent &event);

private:
  float m_time = 0.0f;
};

} // namespace wave