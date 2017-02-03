#ifndef __SURFACE_HPP__
#define __SURFACE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/math/vec2.hpp"
#include "core/math/vec3.hpp"
#include "core/log/logger.hpp"
#include "core/engine_export.h"
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT Surface
{
public:
    Surface();
    virtual ~Surface();

    virtual Vec3 computePoint(const Vec2& uv) const = 0;
    virtual Vec3 computePoint(double u, double v) const = 0;

    virtual size_t getMemSize() const = 0;

    friend Logger& operator<<(Logger& o, const Surface& surface);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SURFACE_HPP__
