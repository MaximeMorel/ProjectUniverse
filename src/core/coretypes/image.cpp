////////////////////////////////////////////////////////////////////////////////
#include "image.hpp"
#include "core/engine.hpp"
////////////////////////////////////////////////////////////////////////////////
ResourceType Image::type("Image");
////////////////////////////////////////////////////////////////////////////////
Image::Image(const std::string& name, const std::string& fileName)
    : super(name, fileName)
{
}
////////////////////////////////////////////////////////////////////////////////
Image::~Image()
{
}
////////////////////////////////////////////////////////////////////////////////
ImagePtr Image::create(const std::string& name, const std::string& fileName)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
Vec2i Image::getResolution() const
{
    return m_resolution;
}
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
    for (auto* codec : getEngine().getCodecs())
    {
        bool success = codec->load(image);
        if (success)
            return image;
    }
    return nullptr;
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
