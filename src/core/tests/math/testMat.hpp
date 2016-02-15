#ifndef __TESTMAT_HPP__
#define __TESTMAT_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "core/math/mat3.hpp"
#include "core/math/mat4.hpp"
////////////////////////////////////////////////////////////////////////////////
class TestMat : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestMat);
    CPPUNIT_TEST(testEqual3);
    CPPUNIT_TEST(testEqual4);
    CPPUNIT_TEST(testMult4);
    CPPUNIT_TEST(testInv3);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void testEqual3();
    void testEqual4();
    void testMult4();
    void testInv3();
};
////////////////////////////////////////////////////////////////////////////////
CPPUNIT_TEST_SUITE_REGISTRATION(TestMat);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTMAT_HPP__
