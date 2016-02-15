#ifndef __CURVEBEZIER_HPP__
#define __CURVEBEZIER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "curve.hpp"
#include "core/math/vec4.hpp"
#include <vector>
////////////////////////////////////////////////////////////////////////////////
/// Bezier curve class (can be rational)
////////////////////////////////////////////////////////////////////////////////
class CurveBezier : public Curve
{
public:
    CurveBezier();
    virtual ~CurveBezier() override;

    /// Add a control point to the curve
    /// \param point Control point to add
    void addControlPoint(const Vec4& point);

    /// Set / replace the ith control point
    /// \param id Id of the control point [0, num control points]
    /// \param point New control point value
    void setControlPoint(size_t id, const Vec4& point);

    /// Get the ith control point
    /// \param id Id of the control point [0, num control points]
    /// \return The ith control point
    const Vec4& getControlPoint(size_t id) const;

    virtual Vec3 computePoint(double u) const override;
    Vec4 computeHPoint(double u) const;

    /// Get the degree of the curve (num of control points - 1)
    /// \return The degree of the curve
    int getDegree() const;

    virtual size_t getMemSize() const override;

    friend Logger& operator<<(Logger& o, const CurveBezier& curve);

private:
    void initMidPoints() const;
    size_t getPointId(size_t iteration, size_t id) const;

    std::vector<Vec4> m_controlPoints;
    mutable std::vector<Vec4> m_midPoints;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __CURVEBEZIER_HPP__
