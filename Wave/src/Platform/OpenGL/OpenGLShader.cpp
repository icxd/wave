#include <Platform/OpenGL/OpenGLShader.hpp>
#include <Wave.hpp>
#include <Wave/Log.hpp>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Wave {

OpenGLShader::OpenGLShader(const std::string &name,
                           const std::string &vertex_src,
                           const std::string &fragment_src) {
  m_name = name;
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

  const GLchar *source = vertex_src.c_str();
  glShaderSource(vertex_shader, 1, &source, 0);

  glCompileShader(vertex_shader);

  GLint is_compiled = 0;
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE) {
    GLint max_length = 0;
    glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length);

    Vec<GLchar> info_log(max_length);
    glGetShaderInfoLog(vertex_shader, max_length, &max_length, &info_log[0]);

    glDeleteShader(vertex_shader);

    WAVE_CORE_ERROR("{}", info_log.data());
    WAVE_CORE_ASSERT(false, "Vertex shader compilation failure!");
    return;
  }

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

  source = fragment_src.c_str();
  glShaderSource(fragment_shader, 1, &source, 0);

  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE) {
    GLint max_length = 0;
    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length);

    Vec<GLchar> info_log(max_length);
    glGetShaderInfoLog(fragment_shader, max_length, &max_length, &info_log[0]);

    glDeleteShader(fragment_shader);
    glDeleteShader(vertex_shader);

    WAVE_CORE_ERROR("{}", info_log.data());
    WAVE_CORE_ASSERT(false, "Fragment shader compilation failure!");
    return;
  }

  m_renderer_id = glCreateProgram();

  glAttachShader(m_renderer_id, vertex_shader);
  glAttachShader(m_renderer_id, fragment_shader);

  glLinkProgram(m_renderer_id);

  GLint is_linked = 0;
  glGetProgramiv(m_renderer_id, GL_LINK_STATUS, (int *)&is_linked);
  if (is_linked == GL_FALSE) {
    GLint max_length = 0;
    glGetProgramiv(m_renderer_id, GL_INFO_LOG_LENGTH, &max_length);

    Vec<GLchar> info_log(max_length);
    glGetProgramInfoLog(m_renderer_id, max_length, &max_length, &info_log[0]);

    glDeleteProgram(m_renderer_id);
    glDeleteShader(fragment_shader);
    glDeleteShader(vertex_shader);

    WAVE_CORE_ERROR("{}", info_log.data());
    WAVE_CORE_ASSERT(false, "Shader link failure!");
    return;
  }

  glDetachShader(m_renderer_id, vertex_shader);
  glDetachShader(m_renderer_id, fragment_shader);
}

OpenGLShader::~OpenGLShader() { glDeleteProgram(m_renderer_id); }

void OpenGLShader::Bind() const { glUseProgram(m_renderer_id); }

void OpenGLShader::Unbind() const { glUseProgram(0); }

void OpenGLShader::UploadUniformInt(const std::string &name, int value) {
  int location = glGetUniformLocation(m_renderer_id, name.c_str());
  WAVE_CORE_ASSERT(location >= 0, "Invalid uniform location");
  glUniform1i(location, value);
}

void OpenGLShader::UploadUniformFloat(const std::string &name, float value) {
  int location = glGetUniformLocation(m_renderer_id, name.c_str());
  WAVE_CORE_ASSERT(location >= 0, "Invalid uniform location");
  glUniform1f(location, value);
}

void OpenGLShader::UploadUniformFloat2(const std::string &name,
                                       const glm::vec2 &values) {
  int location = glGetUniformLocation(m_renderer_id, name.c_str());
  WAVE_CORE_ASSERT(location >= 0, "Invalid uniform location");
  glUniform2f(location, values.x, values.y);
}

void OpenGLShader::UploadUniformFloat3(const std::string &name,
                                       const glm::vec3 &values) {
  int location = glGetUniformLocation(m_renderer_id, name.c_str());
  WAVE_CORE_ASSERT(location >= 0, "Invalid uniform location");
  glUniform3f(location, values.x, values.y, values.z);
}

void OpenGLShader::UploadUniformFloat4(const std::string &name,
                                       const glm::vec4 &values) {
  int location = glGetUniformLocation(m_renderer_id, name.c_str());
  WAVE_CORE_ASSERT(location >= 0, "Invalid uniform location");
  glUniform4f(location, values.x, values.y, values.z, values.w);
}

void OpenGLShader::UploadUniformMat3(const std::string &name,
                                     const glm::mat3 &matrix) {
  int location = glGetUniformLocation(m_renderer_id, name.c_str());
  WAVE_CORE_ASSERT(location >= 0, "Invalid uniform location");
  glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::UploadUniformMat4(const std::string &name,
                                     const glm::mat4 &matrix) {
  int location = glGetUniformLocation(m_renderer_id, name.c_str());
  WAVE_CORE_ASSERT(location >= 0, "Invalid uniform location");
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace Wave