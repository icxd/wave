#include <Platform/OpenGL/OpenGLShader.hpp>
#include <Wave/Renderer/Renderer.hpp>
#include <Wave/Renderer/Shader.hpp>
#include <fstream>
#include <sstream>

namespace wave {

Shader *Shader::Create(const std::string &vertex_src,
                       const std::string &fragment_src) {
  switch (Renderer::GetAPI()) {
  case RendererAPI::API::None:
    WAVE_CORE_ASSERT(false, "RendererAPI::None is not currently supported")
    return nullptr;

  case RendererAPI::API::OpenGL:
    return new OpenGLShader(vertex_src, fragment_src);
  }

  WAVE_CORE_ASSERT(false, "UNREACHABLE");
  return nullptr;
}

Shader *Shader::Create(const std::string &path) {
  std::string vert_path = path + ".vert";
  std::string frag_path = path + ".frag";

  std::ifstream vert(vert_path);
  std::ifstream frag(frag_path);

  std::stringstream vert_buffer, frag_buffer;
  vert_buffer << vert.rdbuf();
  frag_buffer << frag.rdbuf();

  return Shader::Create(vert_buffer.str(), frag_buffer.str());
}

} // namespace wave