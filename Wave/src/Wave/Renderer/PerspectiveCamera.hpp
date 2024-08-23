#pragma once

#include <Wave/Renderer/Camera.hpp>

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Wave {

class PerspectiveCamera : public Camera {
public:
  PerspectiveCamera(float fov, float aspect_ratio, float near = 0.1f,
                    float far = 100.0f);

  virtual const glm::vec3 &GetPosition() const override { return m_position; }
  virtual void SetPosition(const glm::vec3 &position) override {
    m_position = position;
    RecalculateViewMatrix();
  }

  virtual const glm::quat &GetRotation() const override { return m_rotation; }
  virtual void SetRotation(const glm::quat &rotation) override {
    m_rotation = rotation;
    RecalculateViewMatrix();
  }

  virtual const glm::mat4 &GetProjectionMatrix() const override {
    return m_projection_matrix;
  }

  virtual const glm::mat4 &GetViewMatrix() const override {
    return m_view_matrix;
  }

  virtual const glm::mat4 &GetViewProjectionMatrix() const override {
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