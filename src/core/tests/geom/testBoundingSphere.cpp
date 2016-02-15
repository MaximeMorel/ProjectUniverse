////////////////////////////////////////////////////////////////////////////////
#include "testBoundingSphere.hpp"
#include "core/geom/boundingVolume/boundingSphere.hpp"
////////////////////////////////////////////////////////////////////////////////
void TestBoundingSphere::setUp()
{
}
////////////////////////////////////////////////////////////////////////////////
void TestBoundingSphere::tearDown()
{
}
////////////////////////////////////////////////////////////////////////////////
void TestBoundingSphere::testIntersect()
{
    BoundingSphere bs(Vec3(0,0,0), 3);

    CPPUNIT_ASSERT(bs.intersect(Vec3(0)));
    CPPUNIT_ASSERT(bs.intersect(Vec3(1)));
    CPPUNIT_ASSERT(!bs.intersect(Vec3(2)));
    CPPUNIT_ASSERT(!bs.intersect(Vec3(3)));
    CPPUNIT_ASSERT(!bs.intersect(Vec3(4)));
    CPPUNIT_ASSERT(!bs.intersect(Vec3(5)));

    CPPUNIT_ASSERT(bs.intersect(Vec3(0,0,0)));
    CPPUNIT_ASSERT(bs.intersect(Vec3(1,0,0)));
    CPPUNIT_ASSERT(bs.intersect(Vec3(2,0,0)));
    CPPUNIT_ASSERT(bs.intersect(Vec3(3,0,0)));
    CPPUNIT_ASSERT(!bs.intersect(Vec3(4,0,0)));
    CPPUNIT_ASSERT(!bs.intersect(Vec3(5,0,0)));

    bs = BoundingSphere(Vec3(3,3,3), 3);
    CPPUNIT_ASSERT(!bs.intersect(Vec3(0)));
    CPPUNIT_ASSERT(!bs.intersect(Vec3(1)));
    CPPUNIT_ASSERT(bs.intersect(Vec3(2)));
    CPPUNIT_ASSERT(bs.intersect(Vec3(3)));
    CPPUNIT_ASSERT(bs.intersect(Vec3(4)));
    CPPUNIT_ASSERT(!bs.intersect(Vec3(5)));

    CPPUNIT_ASSERT(!bs.intersect(Vec3(0,0,0)));
    CPPUNIT_ASSERT(!bs.intersect(Vec3(1,0,0)));
    CPPUNIT_ASSERT(!bs.intersect(Vec3(2,0,0)));
    CPPUNIT_ASSERT(!bs.intersect(Vec3(3,0,0)));
    CPPUNIT_ASSERT(!bs.intersect(Vec3(4,0,0)));
    CPPUNIT_ASSERT(!bs.intersect(Vec3(5,0,0)));
}
////////////////////////////////////////////////////////////////////////////////
