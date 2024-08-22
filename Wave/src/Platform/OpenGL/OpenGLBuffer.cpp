#include <wavepch.h>

#include <Platform/OpenGL/OpenGLBuffer.hpp>

#include <glad/glad.h>

namespace wave {

OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint size) {
  glCreateBuffers(1, &m_renderer_id);
  this->Bind();
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
  glDeleteBuffers(1, &m_renderer_id);
}

void OpenGLVertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
}

void OpenGLVertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

OpenGLElementBuffer::OpenGLElementBuffer(uint *elements, uint size)
    : m_size(size) {
  glCreateBuffers(1, &m_renderer_id);
  this->Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint), elements,
               GL_STATIC_DRAW);
}

OpenGLElementBuffer::~OpenGLElementBuffer() {
  glDeleteBuffers(1, &m_renderer_id);
}

void OpenGLElementBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
}

void OpenGLElementBuffer::Unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace wave