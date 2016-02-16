#ifndef __BOUNDINGSPHERE_HPP__
#define __BOUNDINGSPHERE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/math/vec3.hpp"
#include <ostream>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class BoundingSphere
{
public:
    BoundingSphere(const Vec3& center, double radius);

    void add(const Vec3& v);

    double distanceSqr(const Vec3& p) const;
    double distance(const Vec3& p) const;

    bool intersect(const Vec3& p) const;

    size_t getMemSize() const;

    friend Logger& operator<<(Logger& o, const BoundingSphere& bs);

    Vec3 center;
    double radius;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __BOUNDINGSPHERE_HPP__
