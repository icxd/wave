#pragma once

#include <Wave/Core.hpp>
#include <Wave/Layer.hpp>

namespace Wave {

class WAVE_API LayerStack {
public:
  LayerStack();
  ~LayerStack();

  void PushLayer(Layer *layer);
  void PushOverlay(Layer *overlay);
  void PopLayer(Layer *layer);
  void PopOverlay(Layer *overlay);

  Vec<Layer *>::iterator begin() { return m_layers.begin(); }
  Vec<Layer *>::iterator end() { return m_layers.end(); }

private:
  Vec<Layer *> m_layers;
  uint m_layer_insert_index = 0;
};

} // namespace Wave