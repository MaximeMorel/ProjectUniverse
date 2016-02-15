#ifndef __TESTBASIC_HPP__
#define __TESTBASIC_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
////////////////////////////////////////////////////////////////////////////////
class TestBasic : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestBasic);
    CPPUNIT_TEST(testAddition);
    CPPUNIT_TEST(testMultiply);
    CPPUNIT_TEST(testTypes);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void testAddition();
    void testMultiply();
    void testTypes();
};
////////////////////////////////////////////////////////////////////////////////
CPPUNIT_TEST_SUITE_REGISTRATION(TestBasic);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTBASIC_HPP__

