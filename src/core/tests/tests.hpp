#ifndef __TESTS_HPP__
#define __TESTS_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
////////////////////////////////////////////////////////////////////////////////
// tests how to
// test header should be included only once
// if there is a compilation error with CPPUNIT_TEST_SUITE_NAMED_REGISTRATION
// it's because it has the same line number of another test header
////////////////////////////////////////////////////////////////////////////////
class TestAll : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestAll);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {}
    void tearDown()
    {}

protected:

private:
};
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestAll, "all");
////////////////////////////////////////////////////////////////////////////////
// add tests here :
#include "testBasic.hpp"
#include "math/testMath.hpp"
#include "geom/testGeom.hpp"
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTS_HPP__
