#pragma once

#include <GLFW/glfw3.h>
#include <stdexcept>


class OpenGLError : public std::logic_error
{
public:
    OpenGLError() : std::logic_error("") {}
};


void APIENTRY dmesg(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam
);

void glfwError(int id, const char* description);