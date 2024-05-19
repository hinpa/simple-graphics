#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

class NoGLFWContext : public std::runtime_error {
  public:
    NoGLFWContext(const std::string &s) : std::runtime_error(s) {}
};

class GLFWLibrary {
  private:
    inline static bool m_glfwIsTerminated = true;

  public:
    ~GLFWLibrary() = delete;
    GLFWLibrary() = delete;
    GLFWLibrary(const GLFWLibrary &) = delete;
    GLFWLibrary(GLFWLibrary &&) = delete;
    GLFWLibrary &operator=(const GLFWLibrary &) = delete;
    GLFWLibrary &operator=(GLFWLibrary &&) = delete;
    static constexpr int SUCCESS = 0;
    static constexpr int FAILURE = 1;
    inline static bool IsTerminated() { return m_glfwIsTerminated; }
    static int Init();
    static void Terminate();
};
