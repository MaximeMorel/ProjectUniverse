////////////////////////////////////////////////////////////////////////////////
#include "textureGL.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/log/logManager.hpp"
#include "core/math/vec2.hpp"
#include "core/coretypes/image.hpp"
#include "opengltools.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
TextureGL::TextureGL(const std::string& name)
    : Texture(name)
    , m_textureId(0)
    , m_internalformat(GL_RGBA8)
    , m_format(GL_RGBA)
    , m_type(GL_UNSIGNED_BYTE)
{
    glGenTextures(1, &m_textureId);
}
////////////////////////////////////////////////////////////////////////////////
TextureGL::TextureGL(const std::string& name, const std::string &fileName)
    : Texture(name, fileName)
    , m_textureId(0)
    , m_internalformat(GL_RGBA8)
    , m_format(GL_RGBA)
    , m_type(GL_UNSIGNED_BYTE)
{
    glGenTextures(1, &m_textureId);
}
////////////////////////////////////////////////////////////////////////////////
TextureGL::~TextureGL()
{
    glDeleteTextures(1, &m_textureId);

    if (isEnginemanaged())
    {
        log().log() << __FUNCTION__ << ": " << *this << std::endl;
        res().delResource(this);
    }
}
////////////////////////////////////////////////////////////////////////////////
TexturePtr TextureGL::create(const std::string& name)
{
    return std::make_shared<TextureGL>(name);
}
////////////////////////////////////////////////////////////////////////////////
TexturePtr TextureGL::create(const std::string& name, const std::string& fileName)
{
    return std::make_shared<TextureGL>(name, fileName);
}
////////////////////////////////////////////////////////////////////////////////
void TextureGL::makeDepth(uint32_t x, uint32_t y)
{
    m_resolution.x = x;
    m_resolution.y = y;
    m_resolution.z = 1;
    m_internalformat = GL_DEPTH_COMPONENT24;
    m_format = GL_DEPTH_COMPONENT;
    m_type = GL_FLOAT;
    m_image = nullptr;
    glTexImage2D(GL_TEXTURE_2D, 0, m_internalformat, m_resolution.x, m_resolution.y, 0, m_format, m_type, nullptr);
}
////////////////////////////////////////////////////////////////////////////////
GLuint TextureGL::getTextureId() const
{
    return m_textureId;
}
////////////////////////////////////////////////////////////////////////////////
void TextureGL::bind(uint32_t unit)
{
    Texture::bind(unit);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}
////////////////////////////////////////////////////////////////////////////////
void TextureGL::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
////////////////////////////////////////////////////////////////////////////////
void TextureGL::setImage(ImagePtr image)
{
    if (!image)
        return;

    if (image->asyncLoadStatus() == 1)
        return;

    Texture::setImage(image);
    bind(m_textureUnit);
    switch (image->imageType())
    {
    case Image::Type::GRAY8:
        m_internalformat = GL_R8;
        m_format = GL_RED;
        m_type = GL_UNSIGNED_BYTE;
        break;
    case Image::Type::GRAYFP32:
        m_internalformat = GL_R32F;
        m_format = GL_RED;
        m_type = GL_FLOAT;
        break;
    case Image::Type::RGB8:
        m_internalformat = GL_RGB8;
        m_format = GL_RGB;
        m_type = GL_UNSIGNED_BYTE;
        break;
    case Image::Type::RGBA8:
        m_internalformat = GL_RGBA8;
        m_format = GL_RGBA;
        m_type = GL_UNSIGNED_BYTE;
        break;
    case Image::Type::RGBFP32:
        m_internalformat = GL_RGB32F;
        m_format = GL_RGB;
        m_type = GL_FLOAT;
        break;
    case Image::Type::RGBAFP32:
        m_internalformat = GL_RGBA32F;
        m_format = GL_RGBA;
        m_type = GL_FLOAT;
        break;
    case Image::Type::RGBADXT1:
        m_internalformat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    default:
        break;
    }

    if (image->imageType() == Image::Type::RGBADXT1)
    {
        GLsizei size = ((m_resolution.x+3)/4)*((m_resolution.y+3)/4)*8;
        glCompressedTexImage2D(GL_TEXTURE_2D, 0, m_internalformat, m_resolution.x, m_resolution.y, 0, size, image->getui8(0, 0));
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, m_internalformat, m_resolution.x, m_resolution.y, 0, m_format, m_type, image->getui8(0, 0));
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}
////////////////////////////////////////////////////////////////////////////////
void TextureGL::resize(Vec2ui resolution)
{
    Texture::resize(resolution);

    glTexImage2D(GL_TEXTURE_2D, 0, m_internalformat, m_resolution.x, m_resolution.y, 0, m_format, m_type, nullptr);
}
////////////////////////////////////////////////////////////////////////////////
void TextureGL::resize(Vec3ui resolution)
{
    Texture::resize(resolution);

    glTexImage3D(GL_TEXTURE_3D, 0, m_internalformat, m_resolution.x, m_resolution.y, resolution.z, 0, m_format, m_type, nullptr);
}
////////////////////////////////////////////////////////////////////////////////
bool TextureGL::reload()
{
    if (m_image)
    {
        uint32_t oldmTime = m_mtime;
        updateMtime();
        if (m_mtime > oldmTime)
        {
            m_image->reload();
            setImage(m_image);
        }
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
void TextureGL::printOn(Logger& o) const
{
    o << "Texture " << m_textureId << " " << getName();
}
////////////////////////////////////////////////////////////////////////////////
