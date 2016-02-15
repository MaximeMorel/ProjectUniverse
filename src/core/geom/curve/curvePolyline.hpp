#ifndef __CURVEPOLYLINE_HPP__
#define __CURVEPOLYLINE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "curve.hpp"
#include <vector>
////////////////////////////////////////////////////////////////////////////////
/// Polyline curve class
////////////////////////////////////////////////////////////////////////////////
class CurvePolyline : public Curve
{
public:
    CurvePolyline(const Vec3& pointA, const Vec3& pointB);
    virtual ~CurvePolyline();

    /// Add a point to the curve
    /// \param v Point to add
    void addPoint(const Vec3& point);

    void setPoint(size_t id, const Vec3& point);
    const Vec3& getPoint(size_t id) const;

    virtual Vec3 computePoint(double u) const override;

    virtual size_t getMemSize() const override;

    friend Logger& operator<<(Logger& o, const CurvePolyline& curve);

private:
    std::vector<Vec3> m_points;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __CURVEPOLYLINE_HPP__
