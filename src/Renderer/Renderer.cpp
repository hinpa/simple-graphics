#include "Renderer.hpp"

void Renderer::ClearBuffer() { m_Objects.clear(); }
void Renderer::Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void Renderer::Draw() {
    for (const auto &i : m_Objects) {
        i.vao->Bind();
        i.shader->Bind();
        glDrawElements(i.mode, i.count, GL_UNSIGNED_INT, nullptr);
    }
    if (ImGui) ImGui();
    glfwSwapBuffers(m_Win);
}

void Renderer::PushObject(VertexArray &vao, Shader &shader, GLenum mode,
                          GLuint count) {
    m_Objects.emplace_back(Object{&vao, &shader, mode, count});
}

void Renderer::MakeContext(GLFWwindow *win) { m_Win = win; }


