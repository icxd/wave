#pragma once

#include <Wave/Core.hpp>
#include <Wave/Events/Event.hpp>
#include <wavepch.h>

namespace wave {

class WAVE_API WindowResizeEvent : public Event {
public:
  WindowResizeEvent(uint width, uint height)
      : m_width(width), m_height(height) {}

  inline uint GetWidth() const { return m_width; }
  inline uint GetHeight() const { return m_height; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << m_width << ", " << m_height;
    return ss.str();
  }

  EVENT_CLASS_TYPE(WindowResize);
  EVENT_CLASS_CATEGORY(EventCategoryApplication);

private:
  uint m_width, m_height;
};

class WAVE_API WindowCloseEvent : public Event {
public:
  WindowCloseEvent() {}

  EVENT_CLASS_TYPE(WindowClose)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WAVE_API AppTickEvent : public Event {
public:
  AppTickEvent() {}

  EVENT_CLASS_TYPE(AppTick)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WAVE_API AppUpdateEvent : public Event {
public:
  AppUpdateEvent() {}

  EVENT_CLASS_TYPE(AppUpdate)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WAVE_API AppRenderEvent : public Event {
public:
  AppRenderEvent() {}

  EVENT_CLASS_TYPE(AppRender)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

} // namespace wave