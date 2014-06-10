#include "tests.hpp"
#include <iostream>
#include <cxxtest/ErrorPrinter.h>
////////////////////////////////////////////////////////////////////////////////
int testRunner()
{
    std::cout << "Starting test runner" << std::endl;
    int status = CxxTest::ErrorPrinter().run();
    std::cout << "Stopping test runner" << std::endl;
    return status;
}
#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
