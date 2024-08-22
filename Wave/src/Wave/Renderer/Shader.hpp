#pragma once

#include <glm/glm.hpp>

namespace wave {

class Shader {
public:
  Shader(const std::string &vertex_src, const std::string &fragment_src);
  ~Shader();

  void Bind() const;
  void Unbind() const;

  void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

private:
  uint m_renderer_id;
};

} // namespace wave