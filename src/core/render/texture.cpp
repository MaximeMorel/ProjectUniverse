////////////////////////////////////////////////////////////////////////////////
#include "texture.hpp"
#include "core/log/logManager.hpp"
#include "renderManager.hpp"
#include "renderPlugin.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/coretypes/image.hpp"
////////////////////////////////////////////////////////////////////////////////
ResourceType Texture::type("Texture");
////////////////////////////////////////////////////////////////////////////////
Texture::Texture(const std::string& name)
    : ResourceFile(name)
    , m_textureUnit(0)
    , m_setImagePending(false)
{
}
////////////////////////////////////////////////////////////////////////////////
Texture::Texture(const std::string& name, const std::string& fileName)
    : ResourceFile(name, fileName)
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
TexturePtr Texture::create(const std::string& name)
{
    TexturePtr tex = render().impl()->createTexture(name);
    if (!tex)
    {
        return nullptr;
    }

    return tex;
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
    if (im->asyncLoadStatus() == true)
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
void Texture::makeDepth(uint32_t x, uint32_t y)
{
}
////////////////////////////////////////////////////////////////////////////////
Vec3ui Texture::getResolution() const
{
    return m_resolution;
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
    if (image)
    {
        Vec2ui resolution = image->resolution();
        m_resolution.x = resolution.x;
        m_resolution.y = resolution.y;
    }
    else
    {
        m_resolution.x = 0;
        m_resolution.y = 0;
    }
}
////////////////////////////////////////////////////////////////////////////////
void Texture::resize(Vec2ui resolution)
{
    m_resolution.x = resolution.x;
    m_resolution.y = resolution.y;
}
////////////////////////////////////////////////////////////////////////////////
void Texture::resize(Vec3ui resolution)
{
    m_resolution = resolution;
}
////////////////////////////////////////////////////////////////////////////////
void Texture::printOn(Logger& o) const
{
    o << "Texture " << getName();
}
////////////////////////////////////////////////////////////////////////////////
