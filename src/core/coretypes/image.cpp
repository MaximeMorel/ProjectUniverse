////////////////////////////////////////////////////////////////////////////////
#include "image.hpp"
#include "core/codecs/codecManager.hpp"
#include "core/log/logManager.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/thread/threadManager.hpp"
////////////////////////////////////////////////////////////////////////////////
ResourceType Image::type("Image");
////////////////////////////////////////////////////////////////////////////////
Image::Info::Info()
    : resolution(0u, 0u)
    , channels(3u)
    , bpc(8u)
    , nummipmaps(1)
    , type(Image::Type::RGB8)
{
}
////////////////////////////////////////////////////////////////////////////////
Image::Image(const std::string& name, const std::string& fileName)
    : super(name, fileName)
    , m_asyncLoadStatus(false)
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
void Image::loadAsync()
{
    std::lock_guard<std::mutex> lock(m_lock);
    // go through image codecs plugins
    for (auto* codec : codecs().getImageCodecs())
    {
        bool success = codec->load(this);
        if (success)
        {
            m_asyncLoadStatus = false;
            return;
        }
    }
    log().log() << "No suitable reader for " << getName() << "\n";
}
////////////////////////////////////////////////////////////////////////////////
ImagePtr Image::create(const std::string& name, const std::string& fileName)
{
    ImagePtr image = std::make_shared<Image>(name, fileName);
    if (!image)
        return nullptr;

    image->m_asyncLoadStatus = true;
    threads().addTask([image]() { image->loadAsync(); });
    return image;
}
////////////////////////////////////////////////////////////////////////////////
void Image::saveAsync(const std::string& filePath)
{
    std::lock_guard<std::mutex> lock(m_lock);
    for (auto* codec : codecs().getImageCodecs())
    {
        bool success = codec->save(this, res().getUserSearchPath() + filePath);
        if (success)
            return;
    }
    log().log() << "No suitable writer for " << getName() << " -> " << filePath << "\n";
}
////////////////////////////////////////////////////////////////////////////////
bool Image::save(const std::string& filePath)
{
    threads().addTask([this, filePath]() { this->saveAsync(filePath); });
    // go through image codecs plugins
    /*for (auto* codec : codecs().getImageCodecs())
    {
        bool success = codec->save(this, res().getUserSearchPath() + filePath);
        if (success)
            return true;
    }
    log().log() << "No suitable writer for " << getName() << " -> " << filePath << "\n";
    return false;*/
    return true;
}
////////////////////////////////////////////////////////////////////////////////
void Image::save(ImagePtr image, const std::string& filePath)
{
    threads().addTask([image, filePath]() { image->saveAsync(filePath); });
}
////////////////////////////////////////////////////////////////////////////////
const char* Image::getSearchPath()
{
    return "";
}
////////////////////////////////////////////////////////////////////////////////
Vec2ui Image::resolution() const
{
    return m_info.resolution;
}
////////////////////////////////////////////////////////////////////////////////
uint32_t Image::width() const
{
    return m_info.resolution.x;
}
////////////////////////////////////////////////////////////////////////////////
uint32_t Image::height() const
{
    return m_info.resolution.y;
}
////////////////////////////////////////////////////////////////////////////////;
uint8_t Image::channels() const
{
    return m_info.channels;
}
////////////////////////////////////////////////////////////////////////////////
uint8_t Image::bitsPerComponent() const
{
    return m_info.bpc;
}
////////////////////////////////////////////////////////////////////////////////
uint8_t Image::bitsPerPixel() const
{
    return m_info.channels * m_info.bpc;
}
////////////////////////////////////////////////////////////////////////////////
Image::Type Image::imageType() const
{
    return m_info.type;
    if (m_info.channels == 1)
    {
        if (m_info.bpc == 8)
            return GRAY8;
        if (m_info.bpc == 32)
            return GRAYFP32;
    }
    else if (m_info.channels == 3)
    {
        if (m_info.bpc == 8)
            return RGB8;
        if (m_info.bpc == 32)
            return RGBFP32;
    }
    else if (m_info.channels == 4)
    {
        if (m_info.bpc == 8)
            return RGBA8;
        if (m_info.bpc == 32)
            return RGBAFP32;
    }
    return UNKNOWN;
}
////////////////////////////////////////////////////////////////////////////////
const Image::Info Image::imageInfo() const
{
    return m_info;
}
////////////////////////////////////////////////////////////////////////////////
void Image::setImageType(Type type)
{
    m_info.type = type;
    switch (type)
    {
    case GRAY8:
        m_info.channels = 1;
        m_info.bpc = 8;
        break;
    case GRAYFP32:
        m_info.channels = 1;
        m_info.bpc = 32;
        break;
    case RGB8:
        m_info.channels = 3;
        m_info.bpc = 8;
        break;
    case RGBA8:
        m_info.channels = 4;
        m_info.bpc = 8;
        break;
    case RGBFP32:
        m_info.channels = 3;
        m_info.bpc = 32;
        break;
    case RGBAFP32:
        m_info.channels = 4;
        m_info.bpc = 32;
        break;
    case RGBADXT1:
        m_info.channels = 3;
        m_info.bpc = 32;
        break;
    default:
        break;
    }
}
////////////////////////////////////////////////////////////////////////////////
void Image::resize(uint32_t w, uint32_t h)
{
    m_buffer.resize(w * h * m_info.channels * (m_info.bpc / 8));
    m_info.resolution.x = w;
    m_info.resolution.y = h;
}
////////////////////////////////////////////////////////////////////////////////
uint8_t* Image::getui8(uint32_t x, uint32_t y)
{
    uint8_t bpp = m_info.channels * (m_info.bpc / 8);
    return &m_buffer[y * m_info.resolution.x * bpp + x * bpp];
}
////////////////////////////////////////////////////////////////////////////////
float& Image::getfp32(uint32_t x, uint32_t y)
{
    return reinterpret_cast<float*>(&m_buffer.front())[y * m_info.resolution.x + x];
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
        for (auto* codec : codecs().getImageCodecs())
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
