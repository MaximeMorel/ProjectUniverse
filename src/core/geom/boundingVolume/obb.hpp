#ifndef __OBB_HPP__
#define __OBB_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/math/vec3.hpp"
#include <ostream>
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class OBB
{
public:
    OBB();

    bool intersect(const Vec3& p) const;

    size_t getMemSize() const;

    friend Logger& operator<<(Logger& o, const OBB& aabb);

};
////////////////////////////////////////////////////////////////////////////////
#endif // __OBB_HPP__
