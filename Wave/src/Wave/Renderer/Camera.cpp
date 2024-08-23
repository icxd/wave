#include <Wave/Renderer/Camera.hpp>
#include <Wave/Renderer/OrthographicCamera.hpp>
#include <Wave/Renderer/PerspectiveCamera.hpp>
#include <memory>

namespace Wave {

Ref<Camera> Camera::CreateOrtho(float left, float right, float bottom,
                                float top, float near, float far) {
  return std::make_shared<OrthographicCamera>(left, right, bottom, top, near,
                                              far);
}
Ref<Camera> Camera::CreatePerspective(float fov, float aspect_ratio, float near,
                                      float far) {
  return std::make_shared<PerspectiveCamera>(fov, aspect_ratio, near, far);
}

} // namespace Wave