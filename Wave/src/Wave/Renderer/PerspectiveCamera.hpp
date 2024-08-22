#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Wave {

class PerspectiveCamera {
public:
  PerspectiveCamera(float fov, float aspect_ratio, float near = 0.1f,
                    float far = 100.0f);

  const glm::vec3 &GetPosition() const { return m_position; }
  void SetPosition(const glm::vec3 &position) {
    m_position = position;
    RecalculateViewMatrix();
  }

  const glm::quat &GetRotation() const { return m_rotation; }
  void SetRotation(const glm::quat &rotation) {
    m_rotation = rotation;
    RecalculateViewMatrix();
  }

  const glm::mat4 &GetProjectionMatrix() const { return m_projection_matrix; }
  const glm::mat4 &GetViewMatrix() const { return m_view_matrix; }
  const glm::mat4 &GetViewProjectionMatrix() const {
    return m_view_projection_matrix;
  }

private:
  void RecalculateViewMatrix();
  void RecalculateProjectionMatrix();

private:
  glm::mat4 m_projection_matrix;
  glm::mat4 m_view_matrix;
  glm::mat4 m_view_projection_matrix;

  glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
  glm::quat m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

  float m_fov, m_aspect_ratio;
  float m_near, m_far;
};

} // namespace Wave