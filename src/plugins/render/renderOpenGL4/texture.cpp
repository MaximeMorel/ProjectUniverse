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
void TextureGL4::setImage(ImageRGBAPtr image)
{
    Texture::setImage(image);
    bind();
    Vec2i r = image->getResolution();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, r.x, r.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image->operator()(0, 0));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}
////////////////////////////////////////////////////////////////////////////////
