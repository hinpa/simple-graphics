#include "./VertexArray.hpp"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_RendererID);
    glBindVertexArray(m_RendererID);
}

void VertexArray::releaseResources() { glDeleteVertexArrays(1, &m_RendererID); }

void VertexArray::AddBuffer(const VertexBuffer &vbo, const VertexIndex &vio,
                            const VertexBufferLayout &layout) const {
    vio.Unbind();
    Bind();
    vbo.Bind();
    const auto &elements = layout.GetElements();
    for (GLuint i = 0, offset = 0; i != elements.size(); ++i) {
        const auto &elem = elements[i];
        glVertexAttribPointer(i, elem.cnt, elem.type, elem.normalized,
                              layout.GetStride(),
                              reinterpret_cast<void *>(offset));
        glEnableVertexAttribArray(i);
        offset += elem.cnt * VertexBufferElement::GetElementSize(elem.type);
    }
    vio.Bind(); // we bind vio to associate vao with this vio. Otherwise, we
                // must always pass it to functions that require it
    Unbind();
    vio.Unbind();
}

void VertexArray::Bind() const { glBindVertexArray(m_RendererID); }

void VertexArray::Unbind() const { glBindVertexArray(0); }