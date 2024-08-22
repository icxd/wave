#include "Wave/Core.hpp"
#include <Platform/OpenGL/OpenGLVertexArray.hpp>

#include <glad/glad.h>

namespace wave {

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
  // clang-format off
  switch(type) {
  case ShaderDataType::None:   WAVE_CORE_ASSERT(false, "ShaderDataType::None is not a valid type"); return 0; 
  case ShaderDataType::Float:  return GL_FLOAT;
  case ShaderDataType::Float2: return GL_FLOAT;
  case ShaderDataType::Float3: return GL_FLOAT;
  case ShaderDataType::Float4: return GL_FLOAT;
  case ShaderDataType::Mat3:   return GL_FLOAT;
  case ShaderDataType::Mat4:   return GL_FLOAT;
  case ShaderDataType::Int:    return GL_INT;
  case ShaderDataType::Int2:   return GL_INT;
  case ShaderDataType::Int3:   return GL_INT;
  case ShaderDataType::Int4:   return GL_INT;
  case ShaderDataType::Bool:   return GL_BOOL;
  }
  // clang-format on

  WAVE_CORE_UNREACHABLE();
  return 0;
}

OpenGLVertexArray::OpenGLVertexArray() {
  glCreateVertexArrays(1, &m_renderer_id);
}

void OpenGLVertexArray::Bind() const { glBindVertexArray(m_renderer_id); }

void OpenGLVertexArray::Unbind() const { glBindVertexArray(0); }

void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> &buffer) {
  WAVE_CORE_ASSERT(buffer->GetLayout().GetElements().size(),
                   "Vertex Buffer has no layout")

  glBindVertexArray(m_renderer_id);
  buffer->Bind();

  uint index = 0;
  const auto &layout = buffer->GetLayout();
  for (const auto &element : layout) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, element.GetComponentCount(),
                          ShaderDataTypeToOpenGLBaseType(element.type),
                          element.normalized ? GL_TRUE : GL_FALSE,
                          layout.GetStride(), (const void *)element.offset);
    index++;
  }

  m_vertex_buffers.push_back(buffer);
}

void OpenGLVertexArray::SetElementBuffer(const Ref<ElementBuffer> &buffer) {
  glBindVertexArray(m_renderer_id);
  buffer->Bind();
  m_element_buffer = buffer;
}

const Vec<Ref<VertexBuffer>> &OpenGLVertexArray::GetVertexBuffers() const {
  return m_vertex_buffers;
}

const Ref<ElementBuffer> &OpenGLVertexArray::GetElementBuffer() const {
  return m_element_buffer;
}

} // namespace wave