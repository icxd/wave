#include <Platform/OpenGL/OpenGLVertexArray.hpp>
#include <Wave/Renderer/Renderer.hpp>
#include <Wave/Renderer/VertexArray.hpp>

namespace wave {

VertexArray *VertexArray::Create() {
  switch (Renderer::GetAPI()) {
  case RendererAPI::API::None:
    WAVE_CORE_ASSERT(false, "RendererAPI::None is not currently supported")
    return nullptr;

  case RendererAPI::API::OpenGL:
    return new OpenGLVertexArray();
  }

  WAVE_CORE_ASSERT(false, "UNREACHABLE");
  return nullptr;
}

} // namespace wave