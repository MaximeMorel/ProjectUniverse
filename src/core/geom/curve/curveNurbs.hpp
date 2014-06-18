#ifndef __CURVENURBS_HPP__
#define __CURVENURBS_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "curve.hpp"
////////////////////////////////////////////////////////////////////////////////
class CurveNurbs : public Curve
{
public:
    CurveNurbs();
    virtual ~CurveNurbs();

    virtual Vec3 computePoint(double u) const override;

    size_t getMemSize() const;

    friend std::ostream& operator<<(std::ostream& o, const CurveNurbs& curve);
    friend Logger& operator<<(Logger& o, const CurveNurbs& curve);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __CURVENURBS_HPP__
