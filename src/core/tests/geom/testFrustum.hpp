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
    void setUp();
    void tearDown();

protected:
    void testIntersect();
};
////////////////////////////////////////////////////////////////////////////////
CPPUNIT_TEST_SUITE_REGISTRATION(TestFrustum);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTFRUSTUM_HPP__
