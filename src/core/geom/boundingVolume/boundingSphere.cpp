////////////////////////////////////////////////////////////////////////////////
#include "boundingSphere.hpp"
#include <cmath>
////////////////////////////////////////////////////////////////////////////////
BoundingSphere::BoundingSphere(const Vec3& center, double radius)
    : center(center)
    , radius(radius)
{
}
////////////////////////////////////////////////////////////////////////////////
void BoundingSphere::add(const Vec3& v)
{

}
////////////////////////////////////////////////////////////////////////////////
double BoundingSphere::distance(const Vec3& p) const
{
    return (p-center).length() - radius;
}
////////////////////////////////////////////////////////////////////////////////
bool BoundingSphere::intersect(const Vec3& p) const
{
    return (p-center).lengthSqr() <= radius*radius;
}
////////////////////////////////////////////////////////////////////////////////
size_t BoundingSphere::getMemSize() const
{
    return sizeof(*this);
}
////////////////////////////////////////////////////////////////////////////////
Logger& operator<<(Logger& o, const BoundingSphere& bs)
{
    return o << bs.center << " / " << bs.radius;
}
////////////////////////////////////////////////////////////////////////////////