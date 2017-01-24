////////////////////////////////////////////////////////////////////////////////
#include "texture.hpp"
#include "core/log/logManager.hpp"
#include "renderManager.hpp"
#include "renderPlugin.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/engine.hpp"
////////////////////////////////////////////////////////////////////////////////
ResourceType Texture::type("Texture");
////////////////////////////////////////////////////////////////////////////////
Texture::Texture(const std::string& name, const std::string& fileName)
    : ResourceFile(name, fileName)
    , m_textureId(0)
    , m_textureUnit(0)
    , m_setImagePending(false)
{

}
////////////////////////////////////////////////////////////////////////////////
Texture::~Texture()
{
    log().log() << __FUNCTION__ << ": " << *this << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
TexturePtr Texture::create(const std::string& name, const std::string& fileName)
{
    TexturePtr tex = render().impl()->createTexture(name, fileName);
    if (!tex)
    {
        return nullptr;
    }

    ImagePtr im = res().createFromFile<Image>(name);
    if (im->asyncLoadStatus() == 1)
    {
        tex->m_setImagePending = true;
        tex->m_image = im;
        //getEngine().thread().getThread(1) = std::thread(&Texture::setImage, tex, im);
    }
    else
    {
        tex->setImage(im);
    }

    return tex;
}
////////////////////////////////////////////////////////////////////////////////
uint32_t Texture::getTextureId() const
{
    return m_textureId;
}
////////////////////////////////////////////////////////////////////////////////
void Texture::bind(uint32_t unit)
{
    if (m_setImagePending)
        setImage(m_image);

    m_textureUnit = unit;
}
////////////////////////////////////////////////////////////////////////////////
void Texture::unbind()
{
}
////////////////////////////////////////////////////////////////////////////////
uint32_t Texture::getUnit() const
{
    return m_textureUnit;
}
////////////////////////////////////////////////////////////////////////////////
void Texture::setImage(ImagePtr image)
{
    m_setImagePending = false;
    m_image = image;
}
////////////////////////////////////////////////////////////////////////////////
void Texture::printOn(Logger& o) const
{
    o << "Texture " << m_textureId << " " << getName();
}
////////////////////////////////////////////////////////////////////////////////
