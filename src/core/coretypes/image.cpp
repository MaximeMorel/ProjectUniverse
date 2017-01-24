////////////////////////////////////////////////////////////////////////////////
#include "image.hpp"
#include "core/engine.hpp"
////////////////////////////////////////////////////////////////////////////////
ResourceType Image::type("Image");
////////////////////////////////////////////////////////////////////////////////
Image::Image(const std::string& name, const std::string& fileName)
    : super(name, fileName)
    , m_resolution(0u, 0u)
    , m_channels(3u)
    , m_bpc(8u)
    , m_asyncLoadStatus(-1)
{
}
////////////////////////////////////////////////////////////////////////////////
Image::~Image()
{
    if (isEnginemanaged())
    {
        log().log() << __FUNCTION__ << ": " << *this << std::endl;
        res().delResource(this);
    }
}
////////////////////////////////////////////////////////////////////////////////
void loadImage(ImagePtr image)
{
    // go through image codecs plugins
    for (auto* codec : getEngine().codecs().getImageCodecs())
    {
        bool success = codec->load(image.get());
        if (success)
        {
            image->m_asyncLoadStatus = 0;
            return;
            //return image;
        }
    }
    log().log() << "No suitable reader for " << image->getName() << "\n";
}
////////////////////////////////////////////////////////////////////////////////
ImagePtr Image::create(const std::string& name, const std::string& fileName)
{
    ImagePtr image = std::make_shared<Image>(name, fileName);
    if (!image)
        return nullptr;

    bool async = true;
    if (async)
    {
        image->m_asyncLoadStatus = 1;
        getEngine().thread().getNextThread() = std::thread(loadImage, image);
    }
    else
    {
        loadImage(image);
    }
    return image;
}
////////////////////////////////////////////////////////////////////////////////
bool Image::save(const std::string& filePath)
{
    // go through image codecs plugins
    for (auto* codec : getEngine().codecs().getImageCodecs())
    {
        bool success = codec->save(this, filePath);
        if (success)
            return true;
    }
    log().log() << "No suitable writer for " << getName() << " -> " << filePath << "\n";
    return false;
}
////////////////////////////////////////////////////////////////////////////////
const char* Image::getSearchPath()
{
    return "";
}
////////////////////////////////////////////////////////////////////////////////
Vec2ui Image::resolution() const
{
    return m_resolution;
}
////////////////////////////////////////////////////////////////////////////////
uint32_t Image::width() const
{
    return m_resolution.x;
}
////////////////////////////////////////////////////////////////////////////////
uint32_t Image::height() const
{
    return m_resolution.y;
}
////////////////////////////////////////////////////////////////////////////////;
uint8_t Image::channels() const
{
    return m_channels;
}
////////////////////////////////////////////////////////////////////////////////
uint8_t Image::bitsPerComponent() const
{
    return m_bpc;
}
////////////////////////////////////////////////////////////////////////////////
uint8_t Image::bitsPerPixel() const
{
    return m_channels * m_bpc;
}
////////////////////////////////////////////////////////////////////////////////
Image::Type Image::imageType() const
{
    if (m_channels == 1)
    {
        if (m_bpc == 8)
            return GRAY8;
        if (m_bpc == 32)
            return GRAYFP32;
    }
    else if (m_channels == 3)
    {
        if (m_bpc == 8)
            return RGB8;
        if (m_bpc == 32)
            return RGBFP32;
    }
    else if (m_channels == 4)
    {
        if (m_bpc == 8)
            return RGBA8;
        if (m_bpc == 32)
            return RGBAFP32;
    }
    return UNKNOWN;
}
////////////////////////////////////////////////////////////////////////////////
void Image::setImageType(Type type)
{
    switch (type)
    {
    case GRAY8:
        m_channels = 1;
        m_bpc = 8;
        break;
    case GRAYFP32:
        m_channels = 1;
        m_bpc = 32;
        break;
    case RGB8:
        m_channels = 3;
        m_bpc = 8;
        break;
    case RGBA8:
        m_channels = 4;
        m_bpc = 8;
        break;
    case RGBFP32:
        m_channels = 3;
        m_bpc = 32;
        break;
    case RGBAFP32:
        m_channels = 4;
        m_bpc = 32;
        break;
    default:
        break;
    }
}
////////////////////////////////////////////////////////////////////////////////
void Image::resize(uint32_t w, uint32_t h)
{
    m_buffer.resize(w * h * m_channels * (m_bpc / 8));
    m_resolution.x = w;
    m_resolution.y = h;
}
////////////////////////////////////////////////////////////////////////////////
uint8_t* Image::getui8(uint32_t x, uint32_t y)
{
    uint8_t bpp = m_channels * (m_bpc / 8);
    return &m_buffer[y * m_resolution.x * bpp + x * bpp];
}
////////////////////////////////////////////////////////////////////////////////
float& Image::getfp32(uint32_t x, uint32_t y)
{
    return reinterpret_cast<float*>(&m_buffer.front())[y * m_resolution.x + x];
}
////////////////////////////////////////////////////////////////////////////////
Vec3ui8 Image::get3ui8(uint32_t x, uint32_t y)
{
    return Vec3ui8(&m_buffer.front());
}
////////////////////////////////////////////////////////////////////////////////
Vec4ui8 Image::get4ui8(uint32_t x, uint32_t y)
{
    return Vec4ui8(&m_buffer.front());
}
////////////////////////////////////////////////////////////////////////////////
bool Image::reload()
{
    uint32_t oldmTime = m_mtime;
    updateMtime();
    if (m_mtime > oldmTime)
    {
        // go through image codecs plugins
        bool reloaded = false;
        for (auto* codec : getEngine().codecs().getImageCodecs())
        {
            bool success = codec->load(this);
            if (success)
            {
                reloaded = true;
                break;
            }
        }
        if (reloaded)
        {
            log().log() << "No suitable reader for " << getName() << "\n";
            return true;
        }
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
