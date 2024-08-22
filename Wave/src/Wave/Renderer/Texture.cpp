#include <wavepch.h>

#include <Platform/OpenGL/OpenGLTexture.hpp>
#include <Wave/Renderer/Renderer.hpp>
#include <Wave/Renderer/Texture.hpp>

namespace wave {

Ref<Texture2D> Texture2D::Create(const std::string &path) {
  switch (Renderer::GetAPI()) {
  case RendererAPI::API::None:
    WAVE_CORE_ASSERT(false, "RendererAPI::None is not currently supported")
    return nullptr;

  case RendererAPI::API::OpenGL:
    return std::make_shared<OpenGLTexture2D>(path);
  }

  WAVE_CORE_ASSERT(false, "UNREACHABLE");
  return nullptr;
}

} // namespace wave