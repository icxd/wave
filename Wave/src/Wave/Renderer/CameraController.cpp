#include <Wave/Core/Input.hpp>
#include <Wave/Core/KeyCodes.hpp>
#include <Wave/Renderer/CameraController.hpp>

namespace Wave {

CameraController::CameraController(float aspect_ratio)
    : m_aspect_ratio(aspect_ratio),
      m_camera(Camera::CreateOrtho(-aspect_ratio * m_zoom_level,
                                   aspect_ratio * m_zoom_level, -m_zoom_level,
                                   m_zoom_level)) {}

void CameraController::OnUpdate(Timestep ts) {
  if (Input::IsKeyPressed(KeyCode::A))
    m_camera_position.x -= m_camera_translation_speed * ts;
  else if (Input::IsKeyPressed(KeyCode::D))
    m_camera_position.x += m_camera_translation_speed * ts;

  if (Input::IsKeyPressed(KeyCode::S))
    m_camera_position.y -= m_camera_translation_speed * ts;
  else if (Input::IsKeyPressed(KeyCode::W))
    m_camera_position.y += m_camera_translation_speed * ts;

  m_camera->SetPosition(m_camera_position);
}
void CameraController::OnEvent(Event &event) {
  EventObserver observer(event);
  observer.Observe<MouseScrolledEvent>(
      WAVE_BIND_FN(CameraController::OnMouseScrolled));
  observer.Observe<WindowResizeEvent>(
      WAVE_BIND_FN(CameraController::OnWindowResized));
}

bool CameraController::OnMouseScrolled(MouseScrolledEvent &event) {
  m_zoom_level -= event.GetYOffset() * 0.25f;
  m_zoom_level = std::max(m_zoom_level, 0.25f);
  m_camera->SetProjection(-m_aspect_ratio * m_zoom_level,
                          m_aspect_ratio * m_zoom_level, -m_zoom_level,
                          m_zoom_level);
  return false;
}

bool CameraController::OnWindowResized(WindowResizeEvent &event) {
  m_aspect_ratio = (float)event.GetWidth() / (float)event.GetHeight();
  m_camera->SetProjection(-m_aspect_ratio * m_zoom_level,
                          m_aspect_ratio * m_zoom_level, -m_zoom_level,
                          m_zoom_level);
  return false;
}

} // namespace Wave