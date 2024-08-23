#pragma once

#include <Wave/Core/Core.hpp>
#include <Wave/Core/Log.hpp>

namespace Wave {

enum class ShaderDataType {
  // clang-format off
  None = 0,
  Float, Float2, Float3, Float4,
  Mat3, Mat4,
  Int, Int2, Int3, Int4,
  Bool,
  // clang-format on
};

static uint ShaderDataTypeSize(ShaderDataType type) {
  // clang-format off
  switch (type) {
  case ShaderDataType::None:   WAVE_CORE_ASSERT(false, "ShaderDataType::None is not a valid type"); return 0;
  case ShaderDataType::Float:  return 4;
  case ShaderDataType::Float2: return 4 * 2;
  case ShaderDataType::Float3: return 4 * 3;
  case ShaderDataType::Float4: return 4 * 4;
  case ShaderDataType::Mat3:   return 4 * 3 * 3;
  case ShaderDataType::Mat4:   return 4 * 4 * 4;
  case ShaderDataType::Int:    return 4;
  case ShaderDataType::Int2:   return 4 * 2;
  case ShaderDataType::Int3:   return 4 * 3;
  case ShaderDataType::Int4:   return 4 * 4;
  case ShaderDataType::Bool:   return 1;
  }
  // clang-format on

  WAVE_CORE_UNREACHABLE();
  return 0;
}

struct BufferElement {
  std::string name;
  ShaderDataType type;
  uint size;
  ulong offset;
  bool normalized;

  BufferElement() {}

  BufferElement(ShaderDataType type, std::string name, bool normalized = false)
      : name(name), type(type), size(ShaderDataTypeSize(type)), offset(0),
        normalized(normalized) {}

  uint GetComponentCount() const {
    // clang-format off
    switch (type) {
    case ShaderDataType::None:   WAVE_CORE_ASSERT(false, "ShaderDataType::None is not a valid type"); return 0; 
    case ShaderDataType::Float:  return 1;
    case ShaderDataType::Float2: return 2;
    case ShaderDataType::Float3: return 3;
    case ShaderDataType::Float4: return 4;
    case ShaderDataType::Mat3:   return 9;
    case ShaderDataType::Mat4:   return 16;
    case ShaderDataType::Int:    return 1;
    case ShaderDataType::Int2:   return 2;
    case ShaderDataType::Int3:   return 3;
    case ShaderDataType::Int4:   return 4;
    case ShaderDataType::Bool:   return 1;
    }
    // clang-format on

    WAVE_CORE_UNREACHABLE();
    return 0;
  }
};

class BufferLayout {
public:
  BufferLayout() {}
  BufferLayout(const std::initializer_list<BufferElement> &elements)
      : m_elements(elements) {
    CalculateOffsetAndStride();
  }

  inline const Vec<BufferElement> &GetElements() const { return m_elements; }

  inline uint GetStride() const { return m_stride; }

  Vec<BufferElement>::iterator begin() { return m_elements.begin(); }
  Vec<BufferElement>::iterator end() { return m_elements.end(); }

  Vec<BufferElement>::const_iterator begin() const {
    return m_elements.begin();
  }
  Vec<BufferElement>::const_iterator end() const { return m_elements.end(); }

private:
  void CalculateOffsetAndStride() {
    uint offset = 0;
    m_stride = 0;
    for (auto &element : m_elements) {
      element.offset = offset;
      offset += element.size;
      m_stride += element.size;
    }
  }

private:
  Vec<BufferElement> m_elements;
  uint m_stride = 0;
};

class VertexBuffer {
public:
  virtual ~VertexBuffer() {}

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual void SetLayout(const BufferLayout &layout) = 0;
  virtual const BufferLayout &GetLayout() const = 0;

  static VertexBuffer *Create(float *vertices, uint size);
};

class ElementBuffer {
public:
  virtual ~ElementBuffer() {}

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual uint GetCount() const = 0;

  static ElementBuffer *Create(uint *elements, uint size);
};

} // namespace Wave
