#include "GLFWLib.h"
#include <GLFW/glfw3.h>

int GLFWLibrary::Init() {
    if (!m_glfwIsTerminated) {
        return SUCCESS;
    }
    if (glfwInit() != GLFW_TRUE) {
        return FAILURE;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_glfwIsTerminated = false;
    return SUCCESS;
}

void GLFWLibrary::Terminate() {
    if (!m_glfwIsTerminated) {
        glfwTerminate();
        m_glfwIsTerminated = true;
    }
}