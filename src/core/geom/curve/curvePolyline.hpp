#ifndef __CURVEPOLYLINE_HPP__
#define __CURVEPOLYLINE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "curve.hpp"
////////////////////////////////////////////////////////////////////////////////
class CurvePolyline : public Curve
{
public:
    CurvePolyline();
    virtual ~CurvePolyline();

    virtual Vec3 computePoint(double u) const override;

    size_t getMemSize() const;

    friend std::ostream& operator<<(std::ostream& o, const CurvePolyline& curve);
    friend Logger& operator<<(Logger& o, const CurvePolyline& curve);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __CURVEPOLYLINE_HPP__
