#ifndef __TESTVEC_HPP__
#define __TESTVEC_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "core/math/vec2.hpp"
////////////////////////////////////////////////////////////////////////////////
class TestVec : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestVec);
    CPPUNIT_TEST(testEqual2);
    CPPUNIT_TEST(testEqual3);
    CPPUNIT_TEST(testEqual4);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {}
    void tearDown()
    {}

protected:
    void testEqual2()
    {
        Vec2 v1(1,1);
        Vec2 v2 = v1;

        CPPUNIT_ASSERT(v1 == v2);

        for(int i=0; i<2; ++i)
        {
            v2 = v1;
            v2[i] = 99;
            CPPUNIT_ASSERT(v1 != v2);
        }
    }

    void testEqual3()
    {
        Vec3 v1(1,2,3);
        Vec3 v2 = v1;

        CPPUNIT_ASSERT(v1 == v2);

        for(int i=0; i<3; ++i)
        {
            v2 = v1;
            v2[i] = 99;
            CPPUNIT_ASSERT(v1 != v2);
        }
    }

    void testEqual4()
    {
        Vec4 v1(1,2,3,4);
        Vec4 v2 = v1;

        CPPUNIT_ASSERT(v1 == v2);

        for(int i=0; i<4; ++i)
        {
            v2 = v1;
            v2[i] = 99;
            CPPUNIT_ASSERT(v1 != v2);
        }
    }


private:
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestVec);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTVEC_HPP__
