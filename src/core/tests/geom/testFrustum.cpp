////////////////////////////////////////////////////////////////////////////////
#include "testFrustum.hpp"
////////////////////////////////////////////////////////////////////////////////
void TestFrustum::setUp()
{
}
////////////////////////////////////////////////////////////////////////////////
void TestFrustum::tearDown()
{
}
////////////////////////////////////////////////////////////////////////////////
void TestFrustum::testIntersect()
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
////////////////////////////////////////////////////////////////////////////////
