#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "../Object/Object.h"

class Texture : IObject {
    GLuint m_RendererID;
    GLubyte *m_LocalBuffer;
    std::string m_texPath;
    GLint m_Width, m_Height, m_BPP;

  private:
    virtual void releaseResources() override;

  public:
    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;
    Texture &operator=(Texture &&) = delete;
    Texture(Texture &&) = delete;
    ~Texture() { releaseResources(); }
    Texture(const std::string &path);
    void Bind(GLuint slot = 0);
    void Unbind();
};