#ifndef __TESTOBB_HPP__
#define __TESTOBB_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
////////////////////////////////////////////////////////////////////////////////
class TestOBB : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestOBB);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
};
////////////////////////////////////////////////////////////////////////////////
CPPUNIT_TEST_SUITE_REGISTRATION(TestOBB);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTOBB_HPP__
