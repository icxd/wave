#pragma once

#include <Wave/Core.hpp>
#include <Wave/Events/Event.hpp>
#include <wavepch.h>

namespace wave {

struct WindowProps {
  std::string title = "WAVE Engine";
  uint width = 1280, height = 720;
};

class WAVE_API Window {
public:
  using EventCallbackFn = std::function<void(Event &)>;

  virtual ~Window() {}

  virtual void OnUpdate() = 0;

  virtual uint GetWidth() const = 0;
  virtual uint GetHeight() const = 0;

  virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
  virtual void SetVSync(bool enabled) = 0;
  virtual bool IsVSync() const = 0;

  inline virtual void *GetNativeWindow() const = 0;

  static Window *Create(const WindowProps &props = WindowProps{});
};

} // namespace wave