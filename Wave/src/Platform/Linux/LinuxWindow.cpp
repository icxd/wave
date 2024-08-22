#include <glad/glad.h>

#include <Platform/Linux/LinuxWindow.hpp>
#include <Platform/OpenGL/OpenGLContext.hpp>

#include <Wave/Core.hpp>
#include <Wave/Events/ApplicationEvent.hpp>
#include <Wave/Events/Event.hpp>
#include <Wave/Events/KeyEvent.hpp>
#include <Wave/Events/MouseEvent.hpp>
#include <Wave/Log.hpp>
#include <Wave/Window.hpp>

namespace wave {

static bool s_glfw_initialized = false;

static void GLFWErrorCallback(int error, const char *message) {
  WAVE_CORE_ERROR("GLFW Error (code: {0}): {1}", error, message);
}

Window *Window::Create(const WindowProps &props) {
  return new LinuxWindow(props);
}

LinuxWindow::LinuxWindow(const WindowProps &props) { Init(props); }
LinuxWindow::~LinuxWindow() { Shutdown(); }

void LinuxWindow::Init(const WindowProps &props) {
  m_data.title = props.title;
  m_data.width = props.width;
  m_data.height = props.height;

  WAVE_CORE_INFO("Creating window {} ({}, {})", props.title, props.width,
                 props.height);

  if (!s_glfw_initialized) {
    int success = glfwInit();
    WAVE_CORE_ASSERT(success, "Could not initialize GLFW!");

    glfwSetErrorCallback(GLFWErrorCallback);

    s_glfw_initialized = true;
  }

  m_window = glfwCreateWindow((int)props.width, (int)props.height,
                              props.title.c_str(), nullptr, nullptr);

  m_context = new OpenGLContext(m_window);
  m_context->Init();

  glfwSetWindowUserPointer(m_window, &m_data);
  SetVSync(true);

  glfwSetWindowSizeCallback(
      m_window, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.event_callback(event);
      });

  glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    WindowCloseEvent event;
    data.event_callback(event);
  });

  glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode,
                                  int action, int mods) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    switch (action) {
    case GLFW_PRESS: {
      KeyPressedEvent event(key, 0);
      data.event_callback(event);
    } break;

    case GLFW_RELEASE: {
      KeyReleasedEvent event(key);
      data.event_callback(event);
    } break;

    case GLFW_REPEAT: {
      KeyPressedEvent event(key, 1);
      data.event_callback(event);
    } break;
    }
  });

  glfwSetCharCallback(m_window, [](GLFWwindow *window, uint keycode) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    KeyTypedEvent event(keycode);
    data.event_callback(event);
  });

  glfwSetMouseButtonCallback(
      m_window, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        switch (action) {
        case GLFW_PRESS: {
          MouseButtonPressedEvent event(button);
          data.event_callback(event);
        } break;

        case GLFW_RELEASE: {
          MouseButtonReleasedEvent event(button);
          data.event_callback(event);
        } break;
        }
      });

  glfwSetScrollCallback(
      m_window, [](GLFWwindow *window, double xoff, double yoff) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float)xoff, (float)yoff);
        data.event_callback(event);
      });

  glfwSetCursorPosCallback(
      m_window, [](GLFWwindow *window, double x, double y) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        MouseMovedEvent event((float)x, (float)y);
        data.event_callback(event);
      });
}

void LinuxWindow::Shutdown() { glfwDestroyWindow(m_window); }

void LinuxWindow::OnUpdate() {
  glfwPollEvents();
  m_context->SwapBuffers();
}

void LinuxWindow::SetVSync(bool enabled) {
  glfwSwapInterval((int)enabled);
  m_data.vsync = enabled;
}

bool LinuxWindow::IsVSync() const { return m_data.vsync; }

} // namespace wave