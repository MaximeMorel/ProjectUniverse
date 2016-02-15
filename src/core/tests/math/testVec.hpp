#ifndef __TESTVEC_HPP__
#define __TESTVEC_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
////////////////////////////////////////////////////////////////////////////////
class TestVec : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestVec);
    CPPUNIT_TEST(testEqual2);
    CPPUNIT_TEST(testEqual3);
    CPPUNIT_TEST(testEqual4);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void testEqual2();
    void testEqual3();
    void testEqual4();
};
////////////////////////////////////////////////////////////////////////////////
CPPUNIT_TEST_SUITE_REGISTRATION(TestVec);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTVEC_HPP__
