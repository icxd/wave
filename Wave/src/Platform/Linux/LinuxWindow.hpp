#pragma once

#include <GLFW/glfw3.h>
#include <Wave/Window.hpp>
#include <wavepch.h>

namespace wave {

class LinuxWindow : public Window {
public:
  LinuxWindow(const WindowProps &props);
  virtual ~LinuxWindow();

  void OnUpdate() override;

  inline uint GetWidth() const override { return m_data.width; }
  inline uint GetHeight() const override { return m_data.height; }

  inline void SetEventCallback(const EventCallbackFn &callback) override {
    m_data.event_callback = callback;
  }
  void SetVSync(bool enabled) override;
  bool IsVSync() const override;

private:
  virtual void Init(const WindowProps &props);
  virtual void Shutdown();

private:
  struct WindowData {
    std::string title;
    uint width, height;
    bool vsync;

    EventCallbackFn event_callback;
  };

private:
  GLFWwindow *m_window;
  WindowData m_data;
};

} // namespace wave
