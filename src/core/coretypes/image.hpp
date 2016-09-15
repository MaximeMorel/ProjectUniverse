#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
#include "buffer.hpp"
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Image : public Resource
{
public:
    Image();
    virtual ~Image();

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:

};
////////////////////////////////////////////////////////////////////////////////
#endif // __SURFACE_HPP__
