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
template <typename T>
class TImage : public ResourceFile
{
public:
    TImage(const std::string& name, const std::string& fileName);
    virtual ~TImage() override;

    static std::shared_ptr<TImage<T>> create(const std::string& name, const std::string& fileName);

    Vec2i getResolution() const;

    T operator()(uint32_t x, uint32_t y) const;
    T& operator()(uint32_t x, uint32_t y);

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    Vec2i m_resolution;     ///< image resolution
    TBuffer<T> m_buffer;     ///< buffer containing image data

private:
    using super = ResourceFile;
};
////////////////////////////////////////////////////////////////////////////////
using ImageRGB = TImage<TVec3<uint8_t>>;
using ImageRGBA = TImage<TVec4<uint8_t>>;
using ImageHDR = TImage<Vec4f>;
////////////////////////////////////////////////////////////////////////////////
#endif // __IMAGE_HPP__
