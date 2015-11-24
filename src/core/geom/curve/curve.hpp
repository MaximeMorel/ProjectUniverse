#ifndef __CURVE_HPP__
#define __CURVE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/math/vec3.hpp"
#include <ostream>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class Curve
{
public:
    Curve() {};
    virtual ~Curve() {};

    virtual Vec3 computePoint(double u) const=0;

    size_t getMemSize() const;

    friend std::ostream& operator<<(std::ostream& o, const Curve& curve);
    friend Logger& operator<<(Logger& o, const Curve& curve);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __CURVE_HPP__
