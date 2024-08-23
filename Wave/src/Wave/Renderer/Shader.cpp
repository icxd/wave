#include <Platform/OpenGL/OpenGLShader.hpp>

#include <Wave/Core/Core.hpp>
#include <Wave/Renderer/Renderer.hpp>
#include <Wave/Renderer/Shader.hpp>

#include <filesystem>
#include <fstream>
#include <sstream>

namespace Wave {

Ref<Shader> Shader::Create(const std::string &name,
                           const std::string &vertex_src,
                           const std::string &fragment_src) {
  switch (Renderer::GetAPI()) {
  case RendererAPI::API::None:
    WAVE_CORE_ASSERT(false, "RendererAPI::None is not currently supported")
    return nullptr;

  case RendererAPI::API::OpenGL:
    return std::make_shared<OpenGLShader>(name, vertex_src, fragment_src);
  }

  WAVE_CORE_ASSERT(false, "UNREACHABLE");
  return nullptr;
}

Ref<Shader> Shader::Create(FilePath path) {
  std::string vert_path = path.replace_extension(".vert");
  std::string frag_path = path.replace_extension(".frag");

  std::ifstream vert(vert_path, std::ios::in | std::ios::binary);
  std::ifstream frag(frag_path, std::ios::in | std::ios::binary);

  std::stringstream vert_buffer, frag_buffer;
  vert_buffer << vert.rdbuf();
  frag_buffer << frag.rdbuf();

  std::filesystem::path filepath = std::filesystem::absolute(vert_path);
  std::string name = filepath.filename().replace_extension().c_str();

  return Shader::Create(name, vert_buffer.str(), frag_buffer.str());
}

void ShaderLibrary::Add(const Ref<Shader> &shader) {
  auto &name = shader->GetName();
  WAVE_CORE_ASSERT(m_shaders.find(name) == m_shaders.end(),
                   "Shader with the same name already exists");
  m_shaders[name] = shader;
}

void ShaderLibrary::Add(const std::string &name, const Ref<Shader> &shader) {
  WAVE_CORE_ASSERT(m_shaders.find(name) == m_shaders.end(),
                   "Shader with the same name already exists");
  m_shaders[name] = shader;
}

Ref<Shader> ShaderLibrary::Load(FilePath path) {
  auto shader = Shader::Create(path);
  Add(shader);
  return shader;
}

Ref<Shader> ShaderLibrary::Load(const std::string &name, FilePath path) {
  auto shader = Shader::Create(path);
  Add(name, shader);
  return shader;
}

Ref<Shader> ShaderLibrary::Get(const std::string &name) {
  WAVE_CORE_ASSERT(m_shaders.find(name) != m_shaders.end(),
                   "Shader with that same name doesn't exist");
  return m_shaders[name];
}

} // namespace Wave