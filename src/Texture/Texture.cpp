
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>
#include "Texture.hpp"

Texture::Texture(const std::string &str)
    : m_RendererID(0), m_LocalBuffer(nullptr), m_texPath(str), m_Width(0),
      m_Height(0), m_BPP(0) {
    stbi_set_flip_vertically_on_load(true);

    m_LocalBuffer = stbi_load(str.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    if (!m_LocalBuffer) {
        std::cout << "Texture image: " << str << " was not found!" << std::endl;
    }

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE); // Do not tile. Clamp
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(
        GL_TEXTURE_2D, 0,
        GL_RGBA8, // GL_RGBA8 is how GL will store data. whereas regular format
                  // is your format of the data you are supplying GL with
        m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}

void Texture::releaseResources() { glDeleteTextures(1, &m_RendererID); }

void Texture::Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

void Texture::Bind(GLuint slot /* = 0*/) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}