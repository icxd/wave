#include <Platform/OpenGL/OpenGLRendererAPI.hpp>

#include <glad/glad.h>

namespace wave {

void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) {
  glClearColor(color.r, color.g, color.b, color.a);
}
void OpenGLRendererAPI::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawElements(const Ref<VertexArray> &vertex_array) {
  glDrawElements(GL_TRIANGLES, vertex_array->GetElementBuffer()->GetCount(),
                 GL_UNSIGNED_INT, nullptr);
}

} // namespace wave