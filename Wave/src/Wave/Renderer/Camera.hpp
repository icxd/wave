#pragma once

#include <Wave/Core/Core.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Wave {

class Camera {
public:
  virtual ~Camera() = default;

  virtual void SetProjection(float left, float right, float bottom,
                             float top) = 0;

  virtual const glm::vec3 &GetPosition() const = 0;
  virtual void SetPosition(const glm::vec3 &position) = 0;

  virtual const glm::quat &GetRotation() const = 0;
  virtual void SetRotation(const glm::quat &rotation) = 0;

  virtual const glm::mat4 &GetProjectionMatrix() const = 0;
  virtual const glm::mat4 &GetViewMatrix() const = 0;
  virtual const glm::mat4 &GetViewProjectionMatrix() const = 0;

  static Ref<Camera> CreateOrtho(float left, float right, float bottom,
                                 float top, float near = -1.0f,
                                 float far = 1.0f);
  static Ref<Camera> CreatePerspective(float fov, float aspect_ratio,
                                       float near = 0.1f, float far = 100.0f);
};

} // namespace Wave