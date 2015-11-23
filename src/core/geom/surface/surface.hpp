#ifndef __SURFACE_HPP__
#define __SURFACE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/math/vec2.hpp"
#include "core/math/vec3.hpp"
#include <ostream>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class Surface
{
public:
    Surface();
    virtual ~Surface();

    virtual Vec3 computePoint(const Vec2& uv) const=0;
    virtual Vec3 computePoint(double u, double v) const=0;

    size_t getMemSize() const;

    friend std::ostream& operator<<(std::ostream& o, const Surface& surface);
    friend Logger& operator<<(Logger& o, const Surface& surface);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SURFACE_HPP__
