#ifndef __SURFACENURBS_HPP__
#define __SURFACENURBS_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "surface.hpp"
////////////////////////////////////////////////////////////////////////////////
class SurfaceNurbs : public Surface
{
public:
    SurfaceNurbs();
    virtual ~SurfaceNurbs() override;

    virtual Vec3 computePoint(const Vec2& uv) const override;
    virtual Vec3 computePoint(double u, double v) const override;

    size_t getMemSize() const;

    friend std::ostream& operator<<(std::ostream& o, const SurfaceNurbs& surface);
    friend Logger& operator<<(Logger& o, const SurfaceNurbs& surface);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SURFACENURBS_HPP__
