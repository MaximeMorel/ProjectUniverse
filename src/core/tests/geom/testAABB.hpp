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
    void setUp();
    void tearDown();

protected:
    void testIntersect();
};
////////////////////////////////////////////////////////////////////////////////
CPPUNIT_TEST_SUITE_REGISTRATION(TestAABB);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTAABB_HPP__
