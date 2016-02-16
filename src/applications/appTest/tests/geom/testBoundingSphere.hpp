#ifndef __TESTBOUNDINGSPHERE_HPP__
#define __TESTBOUNDINGSPHERE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
////////////////////////////////////////////////////////////////////////////////
class TestBoundingSphere : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestBoundingSphere);
    CPPUNIT_TEST(testIntersect);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void testIntersect();
};
////////////////////////////////////////////////////////////////////////////////
CPPUNIT_TEST_SUITE_REGISTRATION(TestBoundingSphere);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTBOUNDINGSPHERE_HPP__
