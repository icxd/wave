#include <Wave.hpp>
#include <Wave/Log.hpp>
#include <Wave/Renderer/Shader.hpp>

#include <glad/glad.h>

namespace wave {

Shader::Shader(const std::string &vertex_src, const std::string &fragment_src) {
  GLuint vertex_shader = glad_glCreateShader(GL_VERTEX_SHADER);

  const GLchar *source = vertex_src.c_str();
  glad_glShaderSource(vertex_shader, 1, &source, 0);

  glad_glCompileShader(vertex_shader);

  GLint is_compiled = 0;
  glad_glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE) {
    GLint max_length = 0;
    glad_glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<GLchar> info_log(max_length);
    glad_glGetShaderInfoLog(vertex_shader, max_length, &max_length,
                            &info_log[0]);

    glad_glDeleteShader(vertex_shader);

    WAVE_CORE_ERROR("{}", info_log.data());
    WAVE_CORE_ASSERT(false, "Vertex shader compilation failure!");
    return;
  }

  GLuint fragment_shader = glad_glCreateShader(GL_FRAGMENT_SHADER);

  source = fragment_src.c_str();
  glad_glShaderSource(fragment_shader, 1, &source, 0);

  glad_glCompileShader(fragment_shader);

  glad_glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE) {
    GLint max_length = 0;
    glad_glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<GLchar> info_log(max_length);
    glad_glGetShaderInfoLog(fragment_shader, max_length, &max_length,
                            &info_log[0]);

    glad_glDeleteShader(fragment_shader);
    glad_glDeleteShader(vertex_shader);

    WAVE_CORE_ERROR("{}", info_log.data());
    WAVE_CORE_ASSERT(false, "Fragment shader compilation failure!");
    return;
  }

  m_renderer_id = glad_glCreateProgram();

  glad_glAttachShader(m_renderer_id, vertex_shader);
  glad_glAttachShader(m_renderer_id, fragment_shader);

  glad_glLinkProgram(m_renderer_id);

  GLint is_linked = 0;
  glad_glGetProgramiv(m_renderer_id, GL_LINK_STATUS, (int *)&is_linked);
  if (is_linked == GL_FALSE) {
    GLint max_length = 0;
    glad_glGetProgramiv(m_renderer_id, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<GLchar> info_log(max_length);
    glad_glGetProgramInfoLog(m_renderer_id, max_length, &max_length,
                             &info_log[0]);

    glad_glDeleteProgram(m_renderer_id);
    glad_glDeleteShader(fragment_shader);
    glad_glDeleteShader(vertex_shader);

    WAVE_CORE_ERROR("{}", info_log.data());
    WAVE_CORE_ASSERT(false, "Shader link failure!");
    return;
  }

  glDetachShader(m_renderer_id, vertex_shader);
  glDetachShader(m_renderer_id, fragment_shader);
}

Shader::~Shader() { glad_glDeleteProgram(m_renderer_id); }

void Shader::Bind() const { glad_glUseProgram(m_renderer_id); }

void Shader::Unbind() const { glad_glUseProgram(0); }

} // namespace wave