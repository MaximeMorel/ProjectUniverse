#ifndef __TESTPLANE_HPP__
#define __TESTPLANE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "core/geom/surface/surfacePlane.hpp"
////////////////////////////////////////////////////////////////////////////////
class TestPlane : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestPlane);
    CPPUNIT_TEST(testPoint);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void testPoint();
};
////////////////////////////////////////////////////////////////////////////////
CPPUNIT_TEST_SUITE_REGISTRATION(TestPlane);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTPLANE_HPP__
