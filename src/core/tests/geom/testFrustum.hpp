#ifndef __TESTFRUSTUM_HPP__
#define __TESTFRUSTUM_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "core/geom/frustum.hpp"
////////////////////////////////////////////////////////////////////////////////
class TestFrustum : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestFrustum);
    CPPUNIT_TEST(testIntersect);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {}
    void tearDown()
    {}

protected:
    void testIntersect()
    {
        Mat4 p = Mat4::ortho(-1, 1, -1, 1, -1, 1);
        Frustum f(p);
        AABB box(Vec3(-0.5, -0.5, -0.5), Vec3(0.5, 0.5, 0.5));
        CPPUNIT_ASSERT(f.intersect(box));

        box = AABB(Vec3(-0.5, -0.5, -0.5), Vec3(1.5, 0.5, 0.5));
        CPPUNIT_ASSERT(f.intersect(box));

        box = AABB(Vec3(0.5, 0.5, 0.5), Vec3(1.5, 1.5, 1.5));
        CPPUNIT_ASSERT(f.intersect(box));

        box = AABB(Vec3(1.5, 1.5, 1.5), Vec3(2.5, 2.5, 2.5));
        CPPUNIT_ASSERT(!f.intersect(box));
    }

private:
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestFrustum);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTFRUSTUM_HPP__
