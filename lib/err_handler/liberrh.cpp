#include <GLFW/glfw3.h>
#include <string>
#include "err_handler.h"


void glfwError(int id, const char* description)
{
    std::string err_str;
    if (id == GLFW_NO_ERROR)
    {
        err_str = "Notification";
    }
    else 
    {
        err_str = "Error";
    }
    fprintf(stderr,"[GLFW %s]: %s\n",err_str.c_str(),description);
    if (id != GLFW_NO_ERROR)
    {
        throw OpenGLError();
    }
}

void APIENTRY dmesg(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam
)
{
    std::string error_translated;
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            error_translated = "Error";
            break;
        default:
            error_translated = "Notification";
    }
    fprintf(stderr,"[OpenGL %s]: %s\n", error_translated.c_str(), message);
    if (GL_DEBUG_TYPE_ERROR == type || type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)
    {
        throw OpenGLError();
    }
}
