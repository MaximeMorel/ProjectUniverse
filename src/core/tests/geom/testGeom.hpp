#ifndef __TESTGEOM_HPP__
#define __TESTGEOM_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "testPlane.hpp"
#include "testFrustum.hpp"
#include "testAABB.hpp"
#include "testBoundingSphere.hpp"
#include "testOBB.hpp"
////////////////////////////////////////////////////////////////////////////////
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
////////////////////////////////////////////////////////////////////////////////
class TestGeom : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestGeom);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {}
    void tearDown()
    {}

protected:

private:
};



CPPUNIT_TEST_SUITE_REGISTRATION(TestGeom);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTGEOM_HPP__
