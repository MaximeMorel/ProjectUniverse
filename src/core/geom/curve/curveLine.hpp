#ifndef __CURVELINE_HPP__
#define __CURVELINE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "curve.hpp"
////////////////////////////////////////////////////////////////////////////////
class CurveLine : public Curve
{
public:
    CurveLine();
    virtual ~CurveLine();

    virtual Vec3 computePoint(double u) const override;

    size_t getMemSize() const;

    friend std::ostream& operator<<(std::ostream& o, const CurveLine& curve);
    //friend Logger& operator<<(Logger& o, const CurveLine& curve);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __CURVELINE_HPP__
