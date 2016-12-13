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

    Vec2i getResolution() const;

protected:
    Vec2i m_resolution;     ///< image resolution

private:
    using super = ResourceFile;

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;
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

    void resize(uint32_t w, uint32_t h);

    T operator()(uint32_t x, uint32_t y) const;
    T& operator()(uint32_t x, uint32_t y);

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    TBuffer<T> m_buffer;     ///< buffer containing image data

private:
    using super = Image;
};
////////////////////////////////////////////////////////////////////////////////
using ImageRGB = TImage<TVec3<uint8_t>>;
using ImageRGBA = TImage<Vec4ui8>;
using ImageHDR = TImage<Vec4f>;

using ImageRGBAPtr = std::shared_ptr<ImageRGBA>;
////////////////////////////////////////////////////////////////////////////////
#endif // __IMAGE_HPP__
