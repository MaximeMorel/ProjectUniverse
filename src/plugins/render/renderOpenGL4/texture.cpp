////////////////////////////////////////////////////////////////////////////////
#include "texture.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/log/logManager.hpp"
#include "opengltools.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
TextureGL4::TextureGL4(const std::string& name, const std::string &fileName)
    : Texture(name, fileName)
{
    glGenTextures(1, &m_textureId);
}
////////////////////////////////////////////////////////////////////////////////
TextureGL4::~TextureGL4()
{
    glDeleteTextures(1, &m_textureId);

    if (isEnginemanaged())
    {
        log().log() << __FUNCTION__ << ": " << *this << std::endl;
        res().delResource(this);
    }
}
////////////////////////////////////////////////////////////////////////////////
TexturePtr TextureGL4::create(const std::string& name, const std::string& fileName)
{
    return std::make_shared<TextureGL4>(name, fileName);
}
////////////////////////////////////////////////////////////////////////////////
void TextureGL4::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}
////////////////////////////////////////////////////////////////////////////////
void TextureGL4::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
////////////////////////////////////////////////////////////////////////////////
void TextureGL4::setImage(ImagePtr image)
{
    if (!image)
        return;

    Texture::setImage(image);
    bind();
    Vec2ui r = image->resolution();
    GLint internalformat = GL_RGBA8;
    GLenum format = GL_RGBA;
    GLenum type = GL_UNSIGNED_BYTE;
    switch (image->imageType())
    {
    case Image::Type::GRAY8:
        internalformat = GL_R8;
        format = GL_RED;
        type = GL_UNSIGNED_BYTE;
        break;
    case Image::Type::GRAYFP32:
        internalformat = GL_R32F;
        format = GL_RED;
        type = GL_FLOAT;
        break;
    case Image::Type::RGB8:
        internalformat = GL_RGB8;
        format = GL_RGB;
        type = GL_UNSIGNED_BYTE;
        break;
    case Image::Type::RGBA8:
        internalformat = GL_RGBA8;
        format = GL_RGBA;
        type = GL_UNSIGNED_BYTE;
        break;
    case Image::Type::RGBFP32:
        internalformat = GL_RGB32F;
        format = GL_RGB;
        type = GL_FLOAT;
        break;
    case Image::Type::RGBAFP32:
        internalformat = GL_RGBA32F;
        format = GL_RGBA;
        type = GL_FLOAT;
        break;
    default:
        break;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, internalformat, r.x, r.y, 0, format, type, image->getui8(0, 0));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}
////////////////////////////////////////////////////////////////////////////////
void TextureGL4::reload()
{
    if (m_image)
    {
        m_image->reload();
        setImage(m_image);
    }
}
////////////////////////////////////////////////////////////////////////////////
