#ifndef __TESTRESOURCEMANAGER_HPP__
#define __TESTRESOURCEMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "core/engine.hpp"
////////////////////////////////////////////////////////////////////////////////
class TestResourceManager : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestResourceManager);
    CPPUNIT_TEST(testResources);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void testResources();

private:
    Engine* m_engine;
};
////////////////////////////////////////////////////////////////////////////////
CPPUNIT_TEST_SUITE_REGISTRATION(TestResourceManager);
////////////////////////////////////////////////////////////////////////////////
#endif // __TESTRESOURCEMANAGER_HPP__
