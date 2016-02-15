////////////////////////////////////////////////////////////////////////////////
#include "testCurve.hpp"
#include "core/geom/curve/curveBezier.hpp"
////////////////////////////////////////////////////////////////////////////////
void TestCurve::setUp()
{
}
////////////////////////////////////////////////////////////////////////////////
void TestCurve::tearDown()
{
}
////////////////////////////////////////////////////////////////////////////////
void TestCurve::testBezier()
{
    CurveBezier curve;
    curve.addControlPoint(Vec4(0.0, 0.0, 0.0, 1.0));
    curve.addControlPoint(Vec4(1.0, 1.0, 0.0, 1.0));
    curve.addControlPoint(Vec4(2.0, 0.0, 0.0, 1.0));

    CPPUNIT_ASSERT(curve.computePoint(0.0) == Vec3(0.0, 0.0, 0.0));
    CPPUNIT_ASSERT(curve.computePoint(0.5) == Vec3(1.0, 0.5, 0.0));
    CPPUNIT_ASSERT(curve.computePoint(1.0) == Vec3(2.0, 0.0, 0.0));
    CPPUNIT_ASSERT_EQUAL(curve.getDegree(), 2);
}
////////////////////////////////////////////////////////////////////////////////
