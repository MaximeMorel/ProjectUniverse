////////////////////////////////////////////////////////////////////////////////
#include "testAABB.hpp"
////////////////////////////////////////////////////////////////////////////////
void TestAABB::setUp()
{
}
////////////////////////////////////////////////////////////////////////////////
void TestAABB::tearDown()
{
}
////////////////////////////////////////////////////////////////////////////////
void TestAABB::testIntersect()
{
    AABB bbox;
    bbox.add(Vec3(-1,-1,-1));
    bbox.add(Vec3());
    CPPUNIT_ASSERT(!bbox.intersect(Vec3(0.5,0.5,0.5)));
    CPPUNIT_ASSERT(bbox.intersect(Vec3(-0.5,-0.5,-0.5)));
    bbox.add(Vec3(1,1,1));
    CPPUNIT_ASSERT(bbox.intersect(Vec3(0.5,0.5,0.5)));
    CPPUNIT_ASSERT(bbox.intersect(Vec3()));
    CPPUNIT_ASSERT(bbox.intersect(Vec3(1,1,1)));
}
////////////////////////////////////////////////////////////////////////////////
