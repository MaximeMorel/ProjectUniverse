#ifndef __TESTAABB_HPP__
#define __TESTAABB_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "core/geom/boundingVolume/aabb.hpp"
////////////////////////////////////////////////////////////////////////////////
class TestAABB : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestAABB);
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

private:
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestAABB);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTAABB_HPP__
