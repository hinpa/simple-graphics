#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cassert>
#include "../../lib/Exceptions/except.h"


/**
 * Specifies the particular attribute. For example, this struct may store vertex position attribute.
 * Does not store elements (this task is left to VertexBuffer)
 */
struct VertexBufferElement {
    GLenum type;
    GLuint cnt;
    GLubyte normalized;
    static GLuint GetElementSize(GLenum type) {
        switch (type) {
        case GL_FLOAT:
            return sizeof(GLfloat);
        case GL_UNSIGNED_BYTE:
            return sizeof(GLuint);
        case GL_UNSIGNED_INT:
            return sizeof(GLubyte);
        }
        return 0;
    }
};

/**
 * Stores information about attribute layout
 */
class VertexBufferLayout {
  private:
    std::vector<VertexBufferElement> m_Elements;
    GLuint m_Stride;

  public:
    typedef std::vector<VertexBufferElement> Container;

  public:
    VertexBufferLayout() : m_Stride(0) {}

  public:
    template <typename T> void AddAttribute(GLuint cnt) {
        assert(cnt < 5);
        m_Elements.push_back({GL_FLOAT, cnt, GL_FALSE});
        throw VerboseNotImplemented;
    }

    template <> void AddAttribute<GLfloat>(GLuint cnt) {
        assert(cnt < 5);
        m_Elements.push_back({GL_FLOAT, cnt, GL_FALSE});
        m_Stride += cnt * sizeof(GLfloat);
    }

    template <> void AddAttribute<GLdouble>(GLuint cnt) {
        assert(cnt < 5);
        m_Elements.push_back({GL_DOUBLE, cnt, GL_FALSE});
        m_Stride += cnt * sizeof(GLdouble);
    }

    template <> void AddAttribute<GLuint>(GLuint cnt) {
        assert(cnt < 5);
        m_Elements.push_back({GL_UNSIGNED_INT, cnt, GL_FALSE});
        m_Stride += cnt * sizeof(GLuint);
    }
    template <> void AddAttribute<GLubyte>(GLuint cnt) {
        assert(cnt < 5);
        m_Elements.push_back({GL_BYTE, cnt, GL_FALSE});
        m_Stride += cnt * sizeof(GLubyte);
    }

    inline const Container &GetElements() const { return m_Elements; }

    inline GLuint GetStride() const { return m_Stride; }
};