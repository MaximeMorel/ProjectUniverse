////////////////////////////////////////////////////////////////////////////////
#include "testPlane.hpp"
#include "core/geom/surface/surfacePlane.hpp"
////////////////////////////////////////////////////////////////////////////////
void TestPlane::setUp()
{
}
////////////////////////////////////////////////////////////////////////////////
void TestPlane::tearDown()
{
}
////////////////////////////////////////////////////////////////////////////////
void TestPlane::testPoint()
{
    double res;

    SurfacePlane p(Vec3(0,0,1), Vec3(0,0,2));
    p = p.normalize();
    res = p.getCoeffs().dot(Vec4(0,0,10,1));
    CPPUNIT_ASSERT(res > 0.0);
    res = p.getCoeffs().dot(Vec4(0,0,-10,1));
    CPPUNIT_ASSERT(res < 0.0);

    p = SurfacePlane(Vec3(0,0,0), Vec3(2,2,2));
    p = p.normalize();
    res = p.getCoeffs().dot(Vec4(1,1,1,1));
    CPPUNIT_ASSERT(res > 0.0);
    res = p.getCoeffs().dot(Vec4(-1,-1,-1,1));
    CPPUNIT_ASSERT(res < 0.0);

    p = SurfacePlane(Vec3(1,1,1), Vec3(2,0,0));
    p = p.normalize();
    res = p.getCoeffs().dot(Vec4(2,90,50,1));
    CPPUNIT_ASSERT(res > 0.0);
    res = p.getCoeffs().dot(Vec4(0,-500,-90,1));
    CPPUNIT_ASSERT(res < 0.0);
}
////////////////////////////////////////////////////////////////////////////////
