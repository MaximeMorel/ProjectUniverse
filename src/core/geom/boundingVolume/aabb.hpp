#ifndef __AABB_HPP__
#define __AABB_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/math/vec3.hpp"
#include "core/log/logger.hpp"
#include "core/engine_export.h"
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT AABB
{
public:
    AABB();
    AABB(const Vec3& pMin, const Vec3& pMax);

    const Vec3& operator[](size_t i) const;

    void add(const Vec3& v);

    void add(const AABB& box);

    bool intersect(const Vec3& p) const;

    size_t getMemSize() const;

    friend Logger& operator<<(Logger& o, const AABB& aabb);

    Vec3 min, max;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __AABB_HPP__
