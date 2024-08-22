#include <wavepch.h>

#include <Platform/OpenGL/OpenGLBuffer.hpp>

#include <glad/glad.h>

namespace wave {

OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint size) {
  glad_glCreateBuffers(1, &m_renderer_id);
  this->Bind();
  glad_glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
  glad_glDeleteBuffers(1, &m_renderer_id);
}

void OpenGLVertexBuffer::Bind() const {
  glad_glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
}

void OpenGLVertexBuffer::Unbind() const {
  glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
}

OpenGLElementBuffer::OpenGLElementBuffer(uint *elements, uint size)
    : m_size(size) {
  glad_glCreateBuffers(1, &m_renderer_id);
  this->Bind();
  glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint), elements,
                    GL_STATIC_DRAW);
}

OpenGLElementBuffer::~OpenGLElementBuffer() {
  glad_glDeleteBuffers(1, &m_renderer_id);
}

void OpenGLElementBuffer::Bind() const {
  glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
}

void OpenGLElementBuffer::Unbind() const {
  glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace wave