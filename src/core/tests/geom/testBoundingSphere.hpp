#ifndef __TESTBOUNDINGSPHERE_HPP__
#define __TESTBOUNDINGSPHERE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "core/geom/boundingVolume/boundingSphere.hpp"
////////////////////////////////////////////////////////////////////////////////
class TestBoundingSphere : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestBoundingSphere);
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

private:
};


CPPUNIT_TEST_SUITE_REGISTRATION(TestBoundingSphere);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTBOUNDINGSPHERE_HPP__
