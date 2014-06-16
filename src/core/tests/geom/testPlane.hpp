#ifndef __TESTPLANE_HPP__
#define __TESTPLANE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "core/geom/plane.hpp"
////////////////////////////////////////////////////////////////////////////////
class TestPlane : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestPlane);
    CPPUNIT_TEST(testPoint);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {}
    void tearDown()
    {}

protected:
    void testPoint()
    {
        double res;

        Plane p(Vec3(0,0,1), Vec3(0,0,2));
        p = p.normalize();
        res = p.getCoeffs().dot(Vec4(0,0,10,1));
        CPPUNIT_ASSERT(res > 0.0);
        res = p.getCoeffs().dot(Vec4(0,0,-10,1));
        CPPUNIT_ASSERT(res < 0.0);

        p = Plane(Vec3(0,0,0), Vec3(2,2,2));
        p = p.normalize();
        res = p.getCoeffs().dot(Vec4(1,1,1,1));
        CPPUNIT_ASSERT(res > 0.0);
        res = p.getCoeffs().dot(Vec4(-1,-1,-1,1));
        CPPUNIT_ASSERT(res < 0.0);

        p = Plane(Vec3(1,1,1), Vec3(2,0,0));
        p = p.normalize();
        res = p.getCoeffs().dot(Vec4(2,90,50,1));
        CPPUNIT_ASSERT(res > 0.0);
        res = p.getCoeffs().dot(Vec4(0,-500,-90,1));
        CPPUNIT_ASSERT(res < 0.0);
    }

private:
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestPlane);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTPLANE_HPP__
