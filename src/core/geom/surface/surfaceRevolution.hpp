#ifndef __SURFACEREVOLUTION_HPP__
#define __SURFACEREVOLUTION_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "surface.hpp"
////////////////////////////////////////////////////////////////////////////////
class SurfaceRevolution : public Surface
{
public:
    SurfaceRevolution();
    virtual ~SurfaceRevolution() override;

    virtual Vec3 computePoint(const Vec2& uv) const override;
    virtual Vec3 computePoint(double u, double v) const override;

    size_t getMemSize() const;

    friend std::ostream& operator<<(std::ostream& o, const SurfaceRevolution& surface);
    friend Logger& operator<<(Logger& o, const SurfaceRevolution& surface);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SURFACEREVOLUTION_HPP__
