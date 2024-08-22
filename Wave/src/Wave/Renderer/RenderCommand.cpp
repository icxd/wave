#include <Wave/Renderer/RenderCommand.hpp>
#include <Wave/Renderer/RendererAPI.hpp>

#include <Platform/OpenGL/OpenGLRendererAPI.hpp>

namespace wave {

RendererAPI *RenderCommand::s_renderer_api = new OpenGLRendererAPI;

}