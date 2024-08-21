#pragma once

#include <Wave/Core.hpp>
#include <Wave/Events/Event.hpp>

namespace wave {

class WAVE_API Layer {
public:
  Layer(const std::string &name = "Layer") : m_debug_name(name) {}
  virtual ~Layer() {}

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate() {}
  virtual void OnEvent(Event &event) {}

  inline const std::string &GetName() const { return m_debug_name; }

protected:
  std::string m_debug_name;
};

} // namespace wave