#pragma once

#include <Wave/Core.hpp>
#include <Wave/Events/ApplicationEvent.hpp>
#include <Wave/ImGui/ImGuiLayer.hpp>
#include <Wave/Layer.hpp>
#include <Wave/LayerStack.hpp>
#include <Wave/Renderer/Buffer.hpp>
#include <Wave/Renderer/Shader.hpp>
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

  uint m_vertex_array;
  OwnRef<Shader> m_shader;
  OwnRef<VertexBuffer> m_vertex_buffer;
  OwnRef<ElementBuffer> m_element_buffer;
};

Application *CreateApplication();

} // namespace wave