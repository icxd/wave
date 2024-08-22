#pragma once

#include <Wave/Core.hpp>
#include <Wave/Core/Timestep.hpp>
#include <Wave/Events/ApplicationEvent.hpp>
#include <Wave/ImGui/ImGuiLayer.hpp>
#include <Wave/Layer.hpp>
#include <Wave/LayerStack.hpp>
#include <Wave/Renderer/Buffer.hpp>
#include <Wave/Renderer/OrthographicCamera.hpp>
#include <Wave/Renderer/Shader.hpp>
#include <Wave/Renderer/VertexArray.hpp>
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

  inline static Application &Get() { return *s_instance; }
  inline Window &GetWindow() { return *m_window; }

private:
  bool onWindowClose(WindowCloseEvent &event);

private:
  static Application *s_instance;

private:
  OwnRef<Window> m_window;
  ImGuiLayer *m_imgui_layer;
  bool m_running = true;
  LayerStack m_layer_stack;
  float m_last_frame_time = 0.0f;
};

Application *CreateApplication();

} // namespace wave