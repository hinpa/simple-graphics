#include "WindowClass.h"
#include "../GLFWLibrary/GLFWLib.h"
#include "../VertexArray/VertexArray.hpp"
#include "../Shader/Shader.hpp"
#include "../Mesh/Mesh.hpp"
#include "../Renderer/Renderer.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>


#include "../../lib/ImGuiLib/imgui.h"
#include "../../lib/ImGuiLib/imgui_impl_glfw.h"
#include "../../lib/ImGuiLib/imgui_impl_opengl3.h"


int WindowClass::Initialize(int width, int height,
                                               const char *title) {
    if (GLFWLibrary::IsTerminated())
        throw NoGLFWContext("Initializing window without GLFW context");
    m_Win = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!m_Win)
        return -1;
    m_Height = height;
    m_Width = width;
    return 0;
}

inline void WindowClass::MakeContextCurrent() { glfwMakeContextCurrent(m_Win); }

inline void WindowClass::Destroy() { glfwDestroyWindow(m_Win); }

WindowClass::~WindowClass() {
    if (!GLFWLibrary::IsTerminated()) {
        Destroy();
    }
}

inline float WindowClass::GetAspectRatio()
{
    return (m_Height > 0) ? 1.f * m_Width / m_Height : 0;
}

void WindowClass::TurnModel(float &y_axis, float &z_axis)
{
    constexpr float rotation_angle_step = 2.f;
    if (glfwGetKey(m_Win, GLFW_KEY_UP) == GLFW_PRESS)
        z_axis += rotation_angle_step;
    if (glfwGetKey(m_Win, GLFW_KEY_DOWN) == GLFW_PRESS)
        z_axis -= rotation_angle_step;
    if (glfwGetKey(m_Win, GLFW_KEY_LEFT) == GLFW_PRESS)
        y_axis -= rotation_angle_step;
    if (glfwGetKey(m_Win, GLFW_KEY_RIGHT) == GLFW_PRESS)
        y_axis += rotation_angle_step;
}
// red square

void WindowClass::Move(float &x, float &y, float &z)
{
    constexpr float move_step = 2.f;
    if (glfwGetKey(m_Win, GLFW_KEY_W) == GLFW_PRESS)
        z += move_step;
    if (glfwGetKey(m_Win, GLFW_KEY_S) == GLFW_PRESS)
        z -= move_step;
    if (glfwGetKey(m_Win, GLFW_KEY_A) == GLFW_PRESS)
        x += move_step;
    if (glfwGetKey(m_Win, GLFW_KEY_D) == GLFW_PRESS)
        x -= move_step;
    if (glfwGetKey(m_Win, GLFW_KEY_Q) == GLFW_PRESS)
        y += move_step;
    if (glfwGetKey(m_Win, GLFW_KEY_E) == GLFW_PRESS)
        y -= move_step;
}

void WindowClass::exec() { // just a window body. Do whatever you want here.
    if (!m_Win)
        throw std::runtime_error("[WindowClass]: running exec without context");
    
    
    Mesh obj("./res/objects/Dragon.obj");

    VertexBufferLayout vbl;
    vbl.AddAttribute<float>(3);
    
    VertexArray vao;
    vao.AddBuffer(obj.GetVBO(), obj.GetVIO(), vbl);

    Shader shader("./res/shaders/vertexShader.vs","./res/shaders/fragmentShader.fs");
    shader.CreateGeomShader("./res/shaders/g.gs");

    glm::mat4 proj = glm::perspective(90.f, GetAspectRatio(), 0.1f, 1000.f);
    glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.f,0.f,-2.f));
    glm::mat4 model = glm::translate(glm::mat4(1.), glm::vec3(0.,0.,0.));
    glm::mat4 camera = glm::translate(glm::mat4(1.), glm::vec3(0.,0.,0.));



    Renderer::PushObject(vao, shader, GL_TRIANGLES, obj.getMeshSize());
    Renderer::MakeContext(m_Win);
    
    // setting up ImGuiContext
    ImGui::CreateContext();

    // backends
    ImGui_ImplGlfw_InitForOpenGL(m_Win, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGuiIO &io = ImGui::GetIO();

    Renderer::ImGui = [&clear_color, &io]() {
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Main ImGui Window");
        ImGui::TextColored(clear_color, "Framerate: %f", io.Framerate);
        ImGui::End();

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    };

    while (!glfwWindowShouldClose(m_Win)) {
        float x = 0, y = 0, z = 0;
        float y_axis = 0, z_axis = 0; //meaningless names
        Move(x,y,z);
        TurnModel(y_axis, z_axis);
        model = glm::rotate(model, glm::radians(y_axis), glm::vec3(0,1,0));
        model = glm::rotate(model, glm::radians(z_axis), glm::vec3(0,0,1));
        view = glm::translate(view, glm::vec3(x,y,z));
        shader.SetUniformMat4f("camera", camera);
        shader.SetUniformMat4f("proj", proj);
        shader.SetUniformMat4f("view", view);
        shader.SetUniformMat4f("model", model);
        Renderer::Clear();

        Renderer::Draw();


        glfwPollEvents();
    }
}