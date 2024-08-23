#pragma once

#include <Wave/Core/Core.hpp>
#include <Wave/Renderer/Buffer.hpp>

namespace Wave {

class VertexArray {
public:
  virtual ~VertexArray() {}

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual void AddVertexBuffer(const Ref<VertexBuffer> &buffer) = 0;
  virtual void SetElementBuffer(const Ref<ElementBuffer> &buffer) = 0;

  virtual const Vec<Ref<VertexBuffer>> &GetVertexBuffers() const = 0;
  virtual const Ref<ElementBuffer> &GetElementBuffer() const = 0;

  static VertexArray *Create();
};

} // namespace Wave