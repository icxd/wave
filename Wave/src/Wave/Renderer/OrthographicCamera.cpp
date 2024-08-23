#include <wavepch.h>

#include <Wave/Renderer/OrthographicCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace Wave {

OrthographicCamera::OrthographicCamera(float left, float right, float bottom,
                                       float top, float near, float far)
    : m_projection_matrix(glm::ortho(left, right, bottom, top, far, near)),
      m_view_matrix(1.0f) {
  m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

void OrthographicCamera::SetProjection(float left, float right, float bottom,
                                       float top) {
  m_projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
  m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

void OrthographicCamera::RecalculateViewMatrix() {
  glm::mat4 rotation_matrix = glm::mat4_cast(m_rotation);
  glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), m_position) * rotation_matrix;

  m_view_matrix = glm::inverse(transform);
  m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

} // namespace Wave