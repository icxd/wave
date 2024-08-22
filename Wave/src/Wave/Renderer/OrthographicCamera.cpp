#include <wavepch.h>

#include <Wave/Renderer/OrthographicCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace wave {

OrthographicCamera::OrthographicCamera(float left, float right, float bottom,
                                       float top, float near, float far)
    : m_projection_matrix(glm::ortho(left, right, bottom, top, far, near)),
      m_view_matrix(1.0f) {
  m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

void OrthographicCamera::RecalculateViewMatrix() {
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position);
  transform =
      glm::rotate(transform, glm::radians(m_rotation), glm::vec3(0, 0, 1));

  m_view_matrix = glm::inverse(transform);
  m_view_projection_matrix = m_projection_matrix * m_view_matrix;
}

} // namespace wave