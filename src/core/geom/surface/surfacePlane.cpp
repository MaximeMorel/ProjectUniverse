////////////////////////////////////////////////////////////////////////////////
#include "surfacePlane.hpp"
////////////////////////////////////////////////////////////////////////////////
SurfacePlane::SurfacePlane(double a, double b, double c, double d)
    : m_coeffs(a, b, c, d)
{
}
////////////////////////////////////////////////////////////////////////////////
SurfacePlane::SurfacePlane(double *coeffs)
    : m_coeffs(coeffs[0], coeffs[1], coeffs[2], coeffs[3])
{
}
////////////////////////////////////////////////////////////////////////////////
SurfacePlane::SurfacePlane(const Vec4& coeffs)
    : m_coeffs(coeffs)
{
}
////////////////////////////////////////////////////////////////////////////////
SurfacePlane::SurfacePlane(const Vec3& point, const Vec3& normal)
    : m_coeffs(normal.x, normal.y, normal.z, -normal.dot(point))
{
}
////////////////////////////////////////////////////////////////////////////////
SurfacePlane::SurfacePlane(const Vec3& a, const Vec3& b, const Vec3& c)
    : SurfacePlane(a, ((b - a).cross(c - a)).normalize())
{
}
////////////////////////////////////////////////////////////////////////////////
const Vec4& SurfacePlane::getCoeffs() const
{
    return m_coeffs;
}
////////////////////////////////////////////////////////////////////////////////
Vec4& SurfacePlane::getCoeffs()
{
    return m_coeffs;
}
////////////////////////////////////////////////////////////////////////////////
Vec3 SurfacePlane::getNormal() const
{
    return Vec3(m_coeffs.x, m_coeffs.y, m_coeffs.z);
}
////////////////////////////////////////////////////////////////////////////////
SurfacePlane SurfacePlane::normalize() const
{
    return SurfacePlane(m_coeffs * (1.0 / getNormal().length()));
}
////////////////////////////////////////////////////////////////////////////////
Vec3 SurfacePlane::computePoint(const Vec2& uv) const
{
    return Vec3();
}
////////////////////////////////////////////////////////////////////////////////
Vec3 SurfacePlane::computePoint(double u, double v) const
{
    return computePoint(Vec2(u, v));
}
////////////////////////////////////////////////////////////////////////////////
size_t SurfacePlane::getMemSize() const
{
    return sizeof(*this);
}
////////////////////////////////////////////////////////////////////////////////
Vec3 SurfacePlane::intersect(const SurfacePlane& p0, const SurfacePlane& p1, const SurfacePlane& p2)
{
    // http://geomalgorithms.com/a05-_intersect-1.html
    return (-p1.getNormal().cross(p2.getNormal()) *
            p0.m_coeffs.w - p2.getNormal().cross(p0.getNormal()) *
            p1.m_coeffs.w - p0.getNormal().cross(p1.getNormal()) *
            p2.m_coeffs.w) / (p0.getNormal().dot(p1.getNormal().cross(p2.getNormal())));
}
////////////////////////////////////////////////////////////////////////////////
Logger& operator<<(Logger& o, const SurfacePlane& SurfacePlane)
{
    return o << SurfacePlane.m_coeffs;
}
////////////////////////////////////////////////////////////////////////////////
