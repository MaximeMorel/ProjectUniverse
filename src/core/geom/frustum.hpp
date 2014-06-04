#ifndef __FRUSTUM_HPP__
#define __FRUSTUM_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/math/mat4.hpp"
#include "core/geom/plane.hpp"
#include "core/geom/aabb.hpp"
#include <ostream>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class Frustum
{
public:
    Frustum(const Mat4& proj);

    bool intersect(const AABB& box) const;

    friend std::ostream& operator<<(std::ostream& o, const Frustum& frustum);
    friend std::ostream& operator<<(Logger& o, const Frustum& frustum);

    Plane planes[6];
};
////////////////////////////////////////////////////////////////////////////////
#endif // __FRUSTUM_HPP__
