#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class IWindow {

  protected:
    int m_Width, m_Height;
    int m_GlewStatus;
    GLFWwindow *m_Win;
    virtual void Destroy() = 0;

  public:
    virtual int Initialize(int width, int height, const char *name) = 0;
    virtual float GetAspectRatio() = 0;
    virtual void MakeContextCurrent() = 0;
    IWindow() : m_Width(0), m_Height(0), m_Win(NULL) {}
    virtual ~IWindow() {}
    virtual void exec() = 0;
};