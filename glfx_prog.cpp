#include <cstddef>
#include <cstdlib>
#include <iostream>
#include "./src/GLFWLibrary/GLFWLib.h"
#include "./src/WindowClass/WindowClass.h"
#include "./lib/err_handler/err_handler.h"

int main() {
    glfwSetErrorCallback(glfwError);
    if (GLFWLibrary::Init()) {
        std::cerr << "Could not create GLFW context\n";
        return EXIT_FAILURE;
    }

    WindowClass win(1920, 1080, "Hello, world!");
    win.MakeContextCurrent();
    if (glewInit() != GLEW_OK) {
        GLFWLibrary::Terminate();
        std::cerr << "Failed to initialize glew!\n";
        return EXIT_FAILURE;
    }
    glDebugMessageCallback(dmesg, NULL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    win.exec();

    GLFWLibrary::Terminate();

    return EXIT_SUCCESS;
}