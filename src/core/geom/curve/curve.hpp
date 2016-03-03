#ifndef __CURVE_HPP__
#define __CURVE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/math/vec3.hpp"
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class Curve
{
public:
    Curve();
    virtual ~Curve();

    virtual Vec3 computePoint(double u) const = 0;

    virtual size_t getMemSize() const = 0;

    friend Logger& operator<<(Logger& o, const Curve& curve);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __CURVE_HPP__
