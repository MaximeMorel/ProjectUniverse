#ifndef __CURVEBEZIER_HPP__
#define __CURVEBEZIER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "curve.hpp"
#include <vector>
////////////////////////////////////////////////////////////////////////////////
/// Bezier curve class
////////////////////////////////////////////////////////////////////////////////
class CurveBezier : public Curve
{
public:
    CurveBezier();
    virtual ~CurveBezier() override;

    /// Add a control point to the curve
    /// \param point Control point to add
    void addControlPoint(const Vec3& point);

    /// Set / replace the ith control point
    /// \param id Id of the control point [0, num control points]
    /// \param point New control point value
    void setControlPoint(size_t id, const Vec3& point);

    /// Get the ith control point
    /// \param id Id of the control point [0, num control points]
    /// \return The ith control point
    const Vec3& getControlPoint(size_t id) const;

    virtual Vec3 computePoint(double u) const override;

    /// Get the degree of the curve (num of control points - 1)
    /// \return The degree of the curve
    int getDegree() const;

    virtual size_t getMemSize() const override;

    friend Logger& operator<<(Logger& o, const CurveBezier& curve);

private:
    std::vector<Vec3> m_controlPoints;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __CURVEBEZIER_HPP__
