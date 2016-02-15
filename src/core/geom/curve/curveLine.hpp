#ifndef __CURVELINE_HPP__
#define __CURVELINE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "curve.hpp"
////////////////////////////////////////////////////////////////////////////////
/// Line curve class
////////////////////////////////////////////////////////////////////////////////
class CurveLine : public Curve
{
public:
    CurveLine(const Vec3& pointA, const Vec3& pointB);
    virtual ~CurveLine();

    void setPoint(size_t id, const Vec3& point);
    const Vec3& getPoint(size_t id) const;

    virtual Vec3 computePoint(double u) const override;

    virtual size_t getMemSize() const override;

    friend Logger& operator<<(Logger& o, const CurveLine& curve);

private:
    Vec3 m_points[2];
};
////////////////////////////////////////////////////////////////////////////////
#endif // __CURVELINE_HPP__
