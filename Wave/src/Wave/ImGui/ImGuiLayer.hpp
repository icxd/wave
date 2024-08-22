#pragma once

#include <Wave/Core.hpp>
#include <Wave/Events/ApplicationEvent.hpp>
#include <Wave/Events/Event.hpp>
#include <Wave/Events/KeyEvent.hpp>
#include <Wave/Events/MouseEvent.hpp>
#include <Wave/Layer.hpp>

namespace Wave {

class WAVE_API ImGuiLayer : public Layer {
public:
  ImGuiLayer() : Layer("ImGuiLayer") {}
  ~ImGuiLayer() = default;

  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnImGuiRender() override;

  void Begin();
  void End();

private:
  float m_time = 0.0f;
};

} // namespace Wave