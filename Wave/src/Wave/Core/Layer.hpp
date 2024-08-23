#pragma once

#include <Wave/Core/Core.hpp>
#include <Wave/Core/Timestep.hpp>
#include <Wave/Events/Event.hpp>

namespace Wave {

class WAVE_API Layer {
public:
  Layer(const std::string &name = "Layer") : m_debug_name(name) {}
  virtual ~Layer() {}

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate(Timestep ts) {}
  virtual void OnEvent(Event &event) {}
  virtual void OnImGuiRender() {}

  inline const std::string &GetName() const { return m_debug_name; }

protected:
  std::string m_debug_name;
};

} // namespace Wave