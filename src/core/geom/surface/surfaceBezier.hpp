#ifndef __SURFACEBEZIER_HPP__
#define __SURFACEBEZIER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "surface.hpp"
////////////////////////////////////////////////////////////////////////////////
class SurfaceBezier : public Surface
{
public:
    SurfaceBezier();
    virtual ~SurfaceBezier() override;

    virtual Vec3 computePoint(const Vec2& uv) const override;
    virtual Vec3 computePoint(double u, double v) const override;

    size_t getMemSize() const;

    friend std::ostream& operator<<(std::ostream& o, const SurfaceBezier& surface);
    friend Logger& operator<<(Logger& o, const SurfaceBezier& surface);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SURFACEBEZIER_HPP__
