////////////////////////////////////////////////////////////////////////////////
#include "curveBezier.hpp"
#include <algorithm>
////////////////////////////////////////////////////////////////////////////////
CurveBezier::CurveBezier()
    : m_controlPoints()
{
}
////////////////////////////////////////////////////////////////////////////////
CurveBezier::~CurveBezier()
{
}
////////////////////////////////////////////////////////////////////////////////
void CurveBezier::addControlPoint(const Vec4& point)
{
    m_controlPoints.push_back(point);
}
////////////////////////////////////////////////////////////////////////////////
void CurveBezier::setControlPoint(size_t id, const Vec4& point)
{
    if (m_controlPoints.size() <= id)
    {
        m_controlPoints.resize(id + 1);
    }
    m_controlPoints[id] = point;
}
////////////////////////////////////////////////////////////////////////////////
const Vec4& CurveBezier::getControlPoint(size_t id) const
{
    return m_controlPoints[id];
}
////////////////////////////////////////////////////////////////////////////////
Vec3 CurveBezier::computePoint(double u) const
{
    Vec4 p = computeHPoint(u);
    return Vec3(p.x, p.y, p.z) / p.w;
}
////////////////////////////////////////////////////////////////////////////////
Vec4 CurveBezier::computeHPoint(double u) const
{
    if (m_midPoints.size() < (m_controlPoints.size() * (m_controlPoints.size() + 1)) / 2)
    {
        initMidPoints();
    }
    for (size_t i = 1; i < m_controlPoints.size(); ++i)
    {
        for (size_t j = 0; j < m_controlPoints.size() - i; ++j)
        {
            m_midPoints[getPointId(i, j)] =
                    m_midPoints[getPointId(i - 1, j)] *
                    (1.0 - u) + m_midPoints[getPointId(i - 1, j + 1)] * u;
        }
    }
    return m_midPoints.back();
}
////////////////////////////////////////////////////////////////////////////////
int CurveBezier::getDegree() const
{
    return m_controlPoints.size() - 1;
}
////////////////////////////////////////////////////////////////////////////////
size_t CurveBezier::getMemSize() const
{
    return sizeof(*this);
}
////////////////////////////////////////////////////////////////////////////////
Logger& operator<<(Logger& o, const CurveBezier& curve)
{
    o << "Bezier curve: degree " << curve.getDegree() << "\n";
    for (const Vec4& v : curve.m_controlPoints)
    {
        o << "\t" << v << "\n";
    }
    o << std::flush;
    return o;
}
////////////////////////////////////////////////////////////////////////////////
void CurveBezier::initMidPoints() const
{
    m_midPoints.reserve((m_controlPoints.size() * (m_controlPoints.size() + 1)) / 2);

    // Put control points in homogenous space
    for (const Vec4& v : m_controlPoints)
    {
        m_midPoints.push_back(Vec4(v.x, v.y, v.z, 1.0) * v.w);
    }
    m_midPoints.resize(m_midPoints.capacity());
}
////////////////////////////////////////////////////////////////////////////////
size_t CurveBezier::getPointId(size_t iteration, size_t id) const
{
    //return ((m_controlPoints.size() * (m_controlPoints.size() + 1)) / 2) -
    //       (((m_controlPoints.size() - iteration) * (m_controlPoints.size() - iteration + 1)) / 2)
    //        + id;
    //return iteration * (m_controlPoints.size() + (1 - iteration) / 2) + id;
    //return iteration * m_controlPoints.size() - (iteration * iteration) / 2 + iteration / 2  + id;
    return iteration * (m_controlPoints.size() - iteration / 2) + iteration / 2 + id;
}
////////////////////////////////////////////////////////////////////////////////
