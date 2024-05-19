#pragma once
#include "../VertexArray/VertexArray.hpp"
#include "../Shader/Shader.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <deque>
#include <functional>

struct Object {
    VertexArray *vao;
    Shader *shader;
    GLenum mode;
    GLuint count;
};

// bad way to do it lol
// use namespace idiot
class Renderer {
  protected:
    inline static std::deque<Object> m_Objects;
    inline static GLFWwindow *m_Win = NULL;
  public:
    ~Renderer() = delete;
    Renderer() = delete;
    // Renderer() {}
    // ~Renderer() { }
    Renderer(const Renderer &) = delete;
    Renderer &operator=(const Renderer &) = delete;
    Renderer &operator=(Renderer &&) = delete;
    Renderer(Renderer &&) = delete;

    static void PushObject(VertexArray &vao, Shader &shader, GLenum mode,
                           GLuint count);
    static void ClearBuffer();
    static void Clear();
    static void Draw();
    static void MakeContext(GLFWwindow *win);

  public:
    inline static std::function<void()> ImGui;
};

