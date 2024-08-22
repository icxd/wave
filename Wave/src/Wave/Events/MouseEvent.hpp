#pragma once

#include <Wave/Core.hpp>
#include <Wave/Events/Event.hpp>
#include <wavepch.h>

namespace Wave {

class WAVE_API MouseMovedEvent : public Event {
public:
  MouseMovedEvent(float x, float y) : m_mousex(x), m_mousey(y) {}

  inline float GetX() const { return m_mousex; }
  inline float GetY() const { return m_mousey; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseMovedEvent: " << m_mousex << ", " << m_mousey;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseMoved)
  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
  float m_mousex, m_mousey;
};

class WAVE_API MouseScrolledEvent : public Event {
public:
  MouseScrolledEvent(float xoffset, float yoffset)
      : m_xoffset(xoffset), m_yoffset(yoffset) {}

  inline float GetXOffset() const { return m_xoffset; }
  inline float GetYOffset() const { return m_yoffset; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseScrolled)
  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
  float m_xoffset, m_yoffset;
};

class WAVE_API MouseButtonEvent : public Event {
public:
  inline int GetMouseButton() const { return m_button; }

  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
protected:
  MouseButtonEvent(int button) : m_button(button) {}

  int m_button;
};

class WAVE_API MouseButtonPressedEvent : public MouseButtonEvent {
public:
  MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << m_button;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseButtonPressed)
};

class WAVE_API MouseButtonReleasedEvent : public MouseButtonEvent {
public:
  MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << m_button;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseButtonReleased)
};

} // namespace Wave