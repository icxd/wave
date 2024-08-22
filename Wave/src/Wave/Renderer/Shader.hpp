#pragma once

namespace wave {

class Shader {
public:
  Shader(const std::string &vertex_src, const std::string &fragment_src);
  ~Shader();

  void Bind() const;
  void Unbind() const;

private:
  uint m_renderer_id;
};

} // namespace wave