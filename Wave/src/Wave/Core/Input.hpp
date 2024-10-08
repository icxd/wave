#pragma once

#include <Wave/Core/Core.hpp>

namespace Wave {

class WAVE_API Input {
public:
  inline static bool IsKeyPressed(int keycode) {
    return s_instance->IsKeyPressedImpl(keycode);
  }

  inline static bool IsMouseButtonPressed(int button) {
    return s_instance->IsMouseButtonPressedImpl(button);
  }
  inline static std::pair<float, float> GetMousePos() {
    return s_instance->GetMousePosImpl();
  }
  inline static float GetMouseX() { return s_instance->GetMouseXImpl(); }
  inline static float GetMouseY() { return s_instance->GetMouseYImpl(); }

protected:
  virtual bool IsKeyPressedImpl(int keycode) = 0;

  virtual bool IsMouseButtonPressedImpl(int button) = 0;
  virtual std::pair<float, float> GetMousePosImpl() = 0;
  virtual float GetMouseXImpl() = 0;
  virtual float GetMouseYImpl() = 0;

private:
  static Input *s_instance;
};

} // namespace Wave