#ifndef __AABB_HPP__
#define __AABB_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/math/vec3.hpp"
#include <ostream>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class AABB
{
public:
    AABB(const Vec3& pMin, const Vec3& pMax);

    const Vec3& operator[](size_t i) const;

    void add(const Vec3& v);

    void add(const AABB& box);

    bool intersect(const Vec3& p) const;

    size_t getMemSize() const;

    friend std::ostream& operator<<(std::ostream& o, const AABB& aabb);
    friend std::ostream& operator<<(Logger& o, const AABB& aabb);

    Vec3 min, max;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __AABB_HPP__
