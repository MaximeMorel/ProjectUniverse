#ifndef __SURFACEPLANE_HPP__
#define __SURFACEPLANE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "surface.hpp"
////////////////////////////////////////////////////////////////////////////////
class SurfacePlane : public Surface
{
public:
    SurfacePlane();
    virtual ~SurfacePlane() override;

    virtual Vec3 computePoint(const Vec2& uv) const override;
    virtual Vec3 computePoint(double u, double v) const override;

    size_t getMemSize() const;

    friend std::ostream& operator<<(std::ostream& o, const SurfacePlane& surface);
    //friend Logger& operator<<(Logger& o, const SurfacePlane& surface);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SURFACEPLANE_HPP__
