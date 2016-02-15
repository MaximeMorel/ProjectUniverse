#ifndef __FRUSTUM_HPP__
#define __FRUSTUM_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/math/vec3.hpp"
#include "core/math/mat4.hpp"
#include "core/geom/surface/surfacePlane.hpp"
#include "core/geom/boundingVolume/aabb.hpp"
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class Frustum
{
public:
    Frustum(const Mat4& proj);

    bool intersect(const Vec3& pt) const;
    bool intersect(const AABB& box) const;

    friend Logger& operator<<(Logger& o, const Frustum& frustum);

    SurfacePlane planes[6];
    Vec3 corners[8];
};
////////////////////////////////////////////////////////////////////////////////
#endif // __FRUSTUM_HPP__
