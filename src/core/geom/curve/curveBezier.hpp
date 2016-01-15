#ifndef __CURVEBEZIER_HPP__
#define __CURVEBEZIER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "curve.hpp"
////////////////////////////////////////////////////////////////////////////////
class CurveBezier : public Curve
{
public:
    CurveBezier();
    virtual ~CurveBezier() override;

    virtual Vec3 computePoint(double u) const override;

    size_t getMemSize() const;

    //friend std::ostream& operator<<(std::ostream& o, const CurveBezier& curve);
    friend Logger& operator<<(Logger& o, const CurveBezier& curve);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __CURVEBEZIER_HPP__
