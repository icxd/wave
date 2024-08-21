#pragma once

#include <Wave/Core.hpp>
#include <Wave/Layer.hpp>

namespace wave {

class WAVE_API LayerStack {
public:
  LayerStack();
  ~LayerStack();

  void PushLayer(Layer *layer);
  void PushOverlay(Layer *overlay);
  void PopLayer(Layer *layer);
  void PopOverlay(Layer *overlay);

  std::vector<Layer *>::iterator begin() { return m_layers.begin(); }
  std::vector<Layer *>::iterator end() { return m_layers.end(); }

private:
  std::vector<Layer *> m_layers;
  std::vector<Layer *>::iterator m_layer_insert;
};

} // namespace wave