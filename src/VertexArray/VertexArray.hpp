#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../BufferLayout/VertexBufferLayout.hpp"
#include "../VertexBuffer/VertexBuffer.hpp"
#include "../VertexIndex/VertexIndex.hpp"
#include "../Object/Object.h"

/**
 * Specifies the layout of each vertex
 */
class VertexArray : IObject {
  private:
    GLuint m_RendererID;

  private:
    virtual void releaseResources() override;

  public:
    VertexArray(const VertexArray &) = delete;
    VertexArray(VertexArray &&) = delete;
    VertexArray &operator=(const VertexArray &) = delete;
    VertexArray &operator=(VertexArray &&) = delete;

  public:
    VertexArray();
    ~VertexArray() { releaseResources(); }

  public:
    void Bind() const;
    void Unbind() const;
    void AddBuffer(const VertexBuffer &vbo, const VertexIndex &vio,
                   const VertexBufferLayout &layout) const;
};