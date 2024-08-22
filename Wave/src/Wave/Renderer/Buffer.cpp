#include <Platform/OpenGL/OpenGLBuffer.hpp>
#include <Wave/Core.hpp>
#include <Wave/Log.hpp>
#include <Wave/Renderer/Buffer.hpp>
#include <Wave/Renderer/Renderer.hpp>

namespace Wave {

VertexBuffer *VertexBuffer::Create(float *vertices, uint size) {
  switch (Renderer::GetAPI()) {
  case RendererAPI::API::None:
    WAVE_CORE_ASSERT(false, "RendererAPI::None is not currently supported")
    return nullptr;

  case RendererAPI::API::OpenGL:
    return new OpenGLVertexBuffer(vertices, size);
  }

  WAVE_CORE_ASSERT(false, "UNREACHABLE");
  return nullptr;
}

ElementBuffer *ElementBuffer::Create(uint *elements, uint size) {
  switch (Renderer::GetAPI()) {
  case RendererAPI::API::None:
    WAVE_CORE_ASSERT(false, "RendererAPI::None is not currently supported")
    return nullptr;

  case RendererAPI::API::OpenGL:
    return new OpenGLElementBuffer(elements, size);
  }

  WAVE_CORE_ASSERT(false, "UNREACHABLE");
  return nullptr;
}

} // namespace Wave
