#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/quaternion.hpp>
#include <wavepch.h>

#include <Wave/Renderer/PerspectiveCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace Wave {

PerspectiveCamera::PerspectiveCamera(float fov, float aspect_ratio, float near,
                                     float far)
    : m_fov(fov), m_aspect_ratio(aspect_ratio), m_near(near), m_far(far) {
  RecalculateProjectionMatrix();
  RecalculateViewMatrix();
}

void PerspectiveCamera::RecalculateViewMatrix() {
  glm::mat4 rotation_matrix = glm::mat4_cast(m_rotation);
  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), m_position) * rotation_matrix;

  m_view_matrix = glm::inverse(transform);
  m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

void PerspectiveCamera::RecalculateProjectionMatrix() {
  m_projection_matrix =
      glm::perspective(glm::radians(m_fov), m_aspect_ratio, m_near, m_far);
  m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

} // namespace Wave