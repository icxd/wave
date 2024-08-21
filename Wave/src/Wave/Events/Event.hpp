#pragma once

#include <Wave/Core.hpp>
#include <fmt/core.h>
#include <fmt/format.h>
#include <type_traits>
#include <wavepch.h>

namespace wave {

enum class EventType {
  None = 0,

  WindowClose,
  WindowResize,
  WindowFocus,
  WindowLostFocus,
  WindowMoved,

  AppTick,
  AppUpdate,
  AppRender,

  KeyPressed,
  KeyReleased,

  MouseButtonPressed,
  MouseButtonReleased,
  MouseMoved,
  MouseScrolled,
};

enum EventCategory {
  None = 0,
  EventCategoryApplication = BIT(0),
  EventCategoryInput = BIT(1),
  EventCategoryKeyboard = BIT(2),
  EventCategoryMouse = BIT(3),
  EventCategoryMouseButton = BIT(4),
};

#define EVENT_CLASS_TYPE(type)                                                 \
  static EventType GetStaticType() { return EventType::type; }                 \
  virtual EventType GetEventType() const override { return GetStaticType(); }  \
  virtual const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)                                         \
  virtual int GetCategoryFlags() const override { return category; }

class WAVE_API Event {
  friend class EventDispatcher;

public:
  virtual EventType GetEventType() const = 0;
  virtual const char *GetName() const = 0;
  virtual int GetCategoryFlags() const = 0;
  virtual std::string ToString() const { return GetName(); }

  inline bool IsInCategory(EventCategory category) {
    return GetCategoryFlags() & category;
  }

public:
  bool Handled = false;
};

class EventDispatcher {
  template <typename T> using EventFn = std::function<bool(T &)>;

public:
  EventDispatcher(Event &event) : m_event(event) {}

  template <typename T> bool Dispatch(EventFn<T> fn) {
    if (m_event.GetEventType() == T::GetStaticType()) {
      m_event.Handled = fn(*(T *)&m_event);
      return true;
    }

    return false;
  }

private:
  Event &m_event;
};

} // namespace wave

inline std::ostream &operator<<(std::ostream &os, const wave::Event &event) {
  return os << event.ToString();
}

template <typename T>
struct fmt::formatter<T,
                      std::enable_if_t<std::is_base_of_v<wave::Event, T>, char>>
    : fmt::formatter<std::string> {
  auto format(const wave::Event &event, format_context &context) const {
    return formatter<std::string>::format(event.ToString(), context);
  }
};