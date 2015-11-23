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
    void setUp()
    {}
    void tearDown()
    {}

protected:
    void testEqual3()
    {
        Mat3 m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Mat3 m2 = m1;

        CPPUNIT_ASSERT(m1 == m2);

        for(int i=0; i<9; ++i)
        {
            m2 = m1;
            CPPUNIT_ASSERT(m1 == m2);
            m2[i] = 99;
            CPPUNIT_ASSERT(m1 != m2);
        }

        m2 = m1;
        m2 = m2.transpose().transpose();
        CPPUNIT_ASSERT(m1 == m2);
    }

    void testEqual4()
    {
        Mat4 m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        Mat4 m2 = m1;

        CPPUNIT_ASSERT(m1 == m2);

        for(int i=0; i<16; ++i)
        {
            m2 = m1;
            m2[i] = 99;
            CPPUNIT_ASSERT(m1 != m2);
        }

        m2 = m1;
        m2 = m2.transpose().transpose();
        CPPUNIT_ASSERT(m1 == m2);
    }

    void testMult4()
    {
        Mat4 m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        Mat4 m2(2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32);

        Mat4 m3 = m1*2;

        CPPUNIT_ASSERT(m3 == m2);

        m3 = m1*m2;
        Mat4 m4(180, 200, 220, 240, 404, 456, 508, 560, 628, 712, 796, 880, 852, 968, 1084, 1200);
        CPPUNIT_ASSERT(m3 == m4);
    }

    void testInv3()
    {
        Mat3 m1(5);
        Mat3 m2 = m1.inverse();

        Mat3 m3 = m1*m2;

        CPPUNIT_ASSERT(m3 == Mat3(1));
    }

private:
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestMat);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTMAT_HPP__
