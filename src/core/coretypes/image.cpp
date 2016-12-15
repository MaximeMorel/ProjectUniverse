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
ImagePtr Image::create(const std::string& name, const std::string& fileName)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
bool Image::save(const std::string& filePath)
{
    return false;
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
uint8_t& Image::getui8(uint32_t x, uint32_t y)
{
    return m_buffer[y * m_resolution.x + x];
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
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TImage<T>::TImage(const std::string& name, const std::string& fileName)
    : super(name, fileName)
{
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
TImage<T>::~TImage()
{
    if (isEnginemanaged())
    {
        log().log() << __FUNCTION__ << ": " << *this << std::endl;
        res().delResource(this);
    }
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::shared_ptr<TImage<T>> TImage<T>::create(const std::string& name, const std::string& fileName)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
template <>
std::shared_ptr<ImageRGBA> ImageRGBA::create(const std::string& name, const std::string& fileName)
{
    std::shared_ptr<ImageRGBA> image = std::make_shared<ImageRGBA>(name, fileName);
    // go through image codecs plugins
    for (auto* codec : getEngine().codecs().getCodecs())
    {
        bool success = codec->load(image);
        if (success)
            return image;
    }
    log().log() << "No suitable reader for " << name << "\n";
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool TImage<T>::save(const std::string& filePath)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
template <>
bool ImageRGBA::save(const std::string& filePath)
{
    // go through image codecs plugins
    for (auto* codec : getEngine().codecs().getCodecs())
    {
        bool success = codec->save(this, filePath);
        if (success)
            return true;
    }
    log().log() << "No suitable writer for " << getName() << " -> " << filePath << "\n";
    return false;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
const char* TImage<T>::getSearchPath()
{
    return "";
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TImage<T>::resize(uint32_t w, uint32_t h)
{
    m_buffer.resize(w * h);
    m_resolution.x = w;
    m_resolution.y = h;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
T TImage<T>::operator()(uint32_t x, uint32_t y) const
{
    return m_buffer[m_resolution.x * y + x];
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
T& TImage<T>::operator()(uint32_t x, uint32_t y)
{
    return m_buffer[m_resolution.x * y + x];
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
size_t TImage<T>::getMemSize() const
{
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TImage<T>::printOn(Logger& o) const
{

}
////////////////////////////////////////////////////////////////////////////////
template class TImage<TVec3<uint8_t>>;
template class TImage<TVec4<uint8_t>>;
template class TImage<Vec4f>;
////////////////////////////////////////////////////////////////////////////////
