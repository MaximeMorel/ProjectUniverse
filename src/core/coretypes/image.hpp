#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resourceFile.hpp"
#include "buffer.hpp"
#include "core/math/vec2.hpp"
#include "core/math/vec3.hpp"
#include "core/math/vec4.hpp"
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class Image;
using ImagePtr = std::shared_ptr<Image>;
////////////////////////////////////////////////////////////////////////////////
class Image : public ResourceFile
{
public:
    Image(const std::string& name, const std::string& fileName);
    virtual ~Image() override;

    static ImagePtr create(const std::string& name, const std::string& fileName);

private:
    using super = ResourceFile;
};
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class TImage : public Image
{
public:
    TImage(const std::string& name, const std::string& fileName);
    virtual ~TImage() override;

    static std::shared_ptr<TImage<T>> create(const std::string& name, const std::string& fileName);

    /// Get the sub search path for this resource
    static const char* getSearchPath();

    Vec2i getResolution() const;

    T operator()(uint32_t x, uint32_t y) const;
    T& operator()(uint32_t x, uint32_t y);

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    Vec2i m_resolution;     ///< image resolution
    TBuffer<T> m_buffer;     ///< buffer containing image data

private:
    using super = Image;
};
////////////////////////////////////////////////////////////////////////////////
using ImageRGB = TImage<TVec3<uint8_t>>;
using ImageRGBA = TImage<TVec4<uint8_t>>;
using ImageHDR = TImage<Vec4f>;
////////////////////////////////////////////////////////////////////////////////
#endif // __IMAGE_HPP__
