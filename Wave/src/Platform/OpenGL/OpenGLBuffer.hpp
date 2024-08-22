#pragma once

#include <Wave/Renderer/Buffer.hpp>

namespace Wave {

class OpenGLVertexBuffer : public VertexBuffer {
public:
  OpenGLVertexBuffer(float *vertices, uint size);
  virtual ~OpenGLVertexBuffer();

  virtual void Bind() const override;
  virtual void Unbind() const override;

  virtual const BufferLayout &GetLayout() const override { return m_layout; }
  virtual void SetLayout(const BufferLayout &layout) override {
    m_layout = layout;
  }

private:
  uint m_renderer_id;
  BufferLayout m_layout;
};

class OpenGLElementBuffer : public ElementBuffer {
public:
  OpenGLElementBuffer(uint *elements, uint size);
  virtual ~OpenGLElementBuffer();

  virtual void Bind() const override;
  virtual void Unbind() const override;

  virtual uint GetCount() const override { return m_size; }

private:
  uint m_renderer_id;
  uint m_size;
};

} // namespace Wave
