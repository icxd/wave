#pragma once

#include <Wave/Renderer/Texture.hpp>

namespace wave {

class OpenGLTexture2D : public Texture2D {
public:
  OpenGLTexture2D(const std::string &path);
  virtual ~OpenGLTexture2D();

  virtual uint GetWidth() const override { return m_width; }
  virtual uint GetHeight() const override { return m_height; }

  virtual void Bind(uint slot = 0) const override;

private:
  std::string m_path;
  uint m_width, m_height;
  uint m_renderer_id;
};

} // namespace wave