#pragma once

#include <string>

namespace wave {

class Shader {
public:
  virtual ~Shader() = default;

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  static Shader *Create(const std::string &vertex_src,
                        const std::string &fragment_src);
  /**
   * @brief Create a Shader using the path to the shader file, without the
   * extension
   *
   * @param path Path to the shader file, no extension
   * @return Shader* Raw pointer to the new shader object
   */
  static Shader *Create(const std::string &path);
};

} // namespace wave