#pragma once

#include <Wave/Core.hpp>
#include <Wave/Events/ApplicationEvent.hpp>
#include <Wave/Layer.hpp>
#include <Wave/LayerStack.hpp>
#include <Wave/Window.hpp>

namespace wave {

class WAVE_API Application {
public:
  Application();
  virtual ~Application();

  void Run();

  void OnEvent(Event &event);

  void PushLayer(Layer *layer);
  void PushOverlay(Layer *overlay);

private:
  bool onWindowClose(WindowCloseEvent &event);

private:
  OwnRef<Window> m_window;
  bool m_running = true;
  LayerStack m_layer_stack;
};

Application *CreateApplication();

} // namespace wave