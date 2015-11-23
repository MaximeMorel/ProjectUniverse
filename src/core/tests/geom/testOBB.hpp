#ifndef __TESTOBB_HPP__
#define __TESTOBB_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "core/geom/boundingVolume/obb.hpp"
////////////////////////////////////////////////////////////////////////////////
class TestOBB : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestOBB);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {}
    void tearDown()
    {}

protected:

private:
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestOBB);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTFRUSTUM_HPP__
__TESTOBB_HPP__
