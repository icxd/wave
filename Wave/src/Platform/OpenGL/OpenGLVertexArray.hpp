#pragma once

#include <Wave/Core/Core.hpp>
#include <Wave/Renderer/Buffer.hpp>
#include <Wave/Renderer/VertexArray.hpp>

namespace Wave {

class OpenGLVertexArray : public VertexArray {
public:
  OpenGLVertexArray();
  virtual ~OpenGLVertexArray() {}

  virtual void Bind() const override;
  virtual void Unbind() const override;

  virtual void AddVertexBuffer(const Ref<VertexBuffer> &buffer) override;
  virtual void SetElementBuffer(const Ref<ElementBuffer> &buffer) override;

  virtual const Vec<Ref<VertexBuffer>> &GetVertexBuffers() const override;
  virtual const Ref<ElementBuffer> &GetElementBuffer() const override;

private:
  uint m_renderer_id;
  Vec<Ref<VertexBuffer>> m_vertex_buffers;
  Ref<ElementBuffer> m_element_buffer;
};

} // namespace Wave