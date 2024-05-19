#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Object/Object.h"

class VertexIndex : IObject {
  private:
    GLuint m_RendererID;

  private:
    virtual void releaseResources() override;

  public:
    VertexIndex(const VertexIndex &) = delete;
    VertexIndex(VertexIndex &&) = delete;
    VertexIndex &operator=(const VertexIndex &) = delete;
    VertexIndex &operator=(VertexIndex &&) = delete;

  public:
    VertexIndex(const void *data, const size_t count, const size_t elem_size);
    ~VertexIndex() { releaseResources(); }

  public:
    void Bind() const;
    void Unbind() const;
};