#include "./VertexIndex.hpp"
#include <sys/wait.h>

VertexIndex::VertexIndex(const void *data, const size_t count,
                         const size_t elem_size) {

    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * elem_size, data,
                 GL_STATIC_DRAW);
    Unbind();
}

void VertexIndex::releaseResources() { glDeleteBuffers(1, &m_RendererID); }

void VertexIndex::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void VertexIndex::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }