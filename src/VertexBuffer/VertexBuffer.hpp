#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Object/Object.h"

class VertexBuffer : IObject {
  private:
    GLuint m_RendererID;

  private:
    virtual void releaseResources() override;

  public:
    VertexBuffer(const VertexBuffer &) = delete;
    VertexBuffer(VertexBuffer &&) = delete;
    VertexBuffer &operator=(const VertexBuffer &) = delete;
    VertexBuffer &operator=(VertexBuffer &&) = delete;
    VertexBuffer(const void *data, const size_t size);

  public:
    ~VertexBuffer() { releaseResources(); }

  public:
    void Bind() const;
    void Unbind() const;
};