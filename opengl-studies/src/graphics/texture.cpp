#include "texture.h"

Texture::Texture(const char* filePath)
{
    // Load the file.
    FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(filePath), filePath);
    // Convert the file to 32 bits so we can use it.
    FIBITMAP* bitmap32 = FreeImage_ConvertTo32Bits(bitmap);


    // Create an OpenGL texture.
    glGenTextures(1, &m_texture);

    // Bind our texture.
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Fill our openGL side texture object.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, FreeImage_GetWidth(bitmap32), FreeImage_GetHeight(bitmap32),
        0, GL_BGRA, GL_UNSIGNED_BYTE, static_cast<void*>(FreeImage_GetBits(bitmap32)));


    // Set texture sampling parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Unbind the texture.
    glBindTexture(GL_TEXTURE_2D, 0);

    // We can unload the images now that the texture data has been buffered with opengl
    FreeImage_Unload(bitmap);
    FreeImage_Unload(bitmap32);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_texture);
}

void Texture::IncRefCount()
{
    m_refCount++;
}

void Texture::DecRefCount()
{
    m_refCount--;
    if (m_refCount == 0)
    {
        delete this;
    }
}

GLuint Texture::GetGLTexture()
{
    return m_texture;
}
