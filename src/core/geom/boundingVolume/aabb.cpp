////////////////////////////////////////////////////////////////////////////////
#include "aabb.hpp"
#include <limits>
////////////////////////////////////////////////////////////////////////////////
AABB::AABB()
: min(std::numeric_limits<double>::max()), max(std::numeric_limits<double>::min())
{
}
////////////////////////////////////////////////////////////////////////////////
AABB::AABB(const Vec3& pMin, const Vec3& pMax)
: min(pMin), max(pMax)
{
}
////////////////////////////////////////////////////////////////////////////////
const Vec3& AABB::operator[](size_t i) const
{
    if(i==0)
        return min;
    return max;
}
////////////////////////////////////////////////////////////////////////////////
void AABB::add(const Vec3& v)
{
    if(v.x < min.x) min.x = v.x;
    else if(v.x > max.x) max.x = v.x;

    if(v.y < min.y) min.y = v.y;
    else if(v.y > max.y) max.y = v.y;

    if(v.z < min.z) min.z = v.z;
    else if(v.z > max.z) max.z = v.z;
}
////////////////////////////////////////////////////////////////////////////////
void AABB::add(const AABB& box)
{
    add(box.min);
    add(box.max);
}
////////////////////////////////////////////////////////////////////////////////
bool AABB::intersect(const Vec3& p) const
{
    return (p.x >= min.x && p.x <= max.x &&
            p.y >= min.y && p.y <= max.y &&
            p.z >= min.z && p.z <= max.z);
}
////////////////////////////////////////////////////////////////////////////////
size_t AABB::getMemSize() const
{
    return sizeof(*this);
}
////////////////////////////////////////////////////////////////////////////////
/*std::ostream& operator<<(std::ostream& o, const AABB& aabb)
{
    return o << aabb.min << " / " << aabb.max << " [" << aabb.max.x-aabb.min.x << ", " << aabb.max.y-aabb.min.y << ", " << aabb.max.z-aabb.min.z << "]";
}*/
////////////////////////////////////////////////////////////////////////////////
Logger& operator<<(Logger& o, const AABB& aabb)
{
    return o << aabb.min << " / " << aabb.max << " [" << aabb.max.x-aabb.min.x << ", " << aabb.max.y-aabb.min.y << ", " << aabb.max.z-aabb.min.z << "]";
}
////////////////////////////////////////////////////////////////////////////////
