#pragma once

#include <Wave/Core.hpp>
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
  float m_time = 0.0f;
};

} // namespace wave