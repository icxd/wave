#include <Wave/Core.hpp>
#include <Wave/Log.hpp>

#include <Platform/OpenGL/OpenGLTexture.hpp>

#include <glad/glad.h>
#include <stb_image.h>

namespace Wave {

OpenGLTexture2D::OpenGLTexture2D(const std::string &path) : m_path(path) {
  int width, height, channels;
  stbi_set_flip_vertically_on_load(1);
  stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  if (!data) {
    WAVE_CORE_ERROR("Failed to load image: {}", path);
    WAVE_CORE_ASSERT(false, "Failed to load image");
  }
  m_width = width;
  m_height = height;

  // clang-format off
  GLenum internal_format = 0, format = 0;
  switch (channels) {
  case 3: internal_format = GL_RGB8; format = GL_RGB; break;
  case 4: internal_format = GL_RGBA8; format = GL_RGBA; break;
  default: break;
  }
  //clang-format on

  WAVE_CORE_ASSERT(internal_format & format, "Unrecognized image format");

  glCreateTextures(GL_TEXTURE_2D, 1, &m_renderer_id);
  glTextureStorage2D(m_renderer_id, 1, internal_format, m_width, m_height);

  glTextureParameteri(m_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(m_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureSubImage2D(m_renderer_id, 0, 0, 0, m_width, m_height, format,
                      GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D() { glDeleteTextures(1, &m_renderer_id); }

void OpenGLTexture2D::Bind(uint slot) const {
  glBindTextureUnit(slot, m_renderer_id);
}

} // namespace Wave