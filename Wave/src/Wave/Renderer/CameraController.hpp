#pragma once

#include <Wave/Core/Core.hpp>
#include <Wave/Core/Timestep.hpp>
#include <Wave/Events/ApplicationEvent.hpp>
#include <Wave/Events/Event.hpp>
#include <Wave/Events/MouseEvent.hpp>
#include <Wave/Renderer/Camera.hpp>

namespace Wave {

class CameraController {
public:
  CameraController(float aspect_ratio);

  void OnUpdate(Timestep ts);
  void OnEvent(Event &event);

  const Ref<Camera> &GetCamera() const { return m_camera; }

  float GetZoomLevel() const { return m_zoom_level; }
  void SetZoomLevel(float level) { m_zoom_level = level; }

private:
  bool OnMouseScrolled(MouseScrolledEvent &event);
  bool OnWindowResized(WindowResizeEvent &event);

private:
  float m_aspect_ratio;
  float m_zoom_level = 1.0f;
  Ref<Camera> m_camera;

  glm::vec3 m_camera_position = {0.0f, 0.0f, 0.0f};
  glm::quat m_camera_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
  float m_camera_translation_speed = 1.0f, m_camera_rotation_speed = 1.0f;
};

} // namespace Wave