#pragma once

#include <Wave/Core/Core.hpp>

#include <string>
#include <unordered_map>

namespace Wave {

class Shader {
public:
  virtual ~Shader() = default;

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual const std::string &GetName() const = 0;

  static Ref<Shader> Create(const std::string &name,
                            const std::string &vertex_src,
                            const std::string &fragment_src);
  /**
   * Create a Shader using the path to the shader file, without the
   * extension
   */
  static Ref<Shader> Create(FilePath path);
};

class ShaderLibrary {
public:
  void Add(const Ref<Shader> &shader);
  void Add(const std::string &name, const Ref<Shader> &shader);
  Ref<Shader> Load(FilePath path);
  Ref<Shader> Load(const std::string &name, FilePath path);

  Ref<Shader> Get(const std::string &name);

private:
  std::unordered_map<std::string, Ref<Shader>> m_shaders;
};

} // namespace Wave