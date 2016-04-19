#ifndef __APPTEST_HPP__
#define __APPTEST_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/application.hpp"
////////////////////////////////////////////////////////////////////////////////
extern "C" const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" Application* getAppInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" void closeAppInstance();
////////////////////////////////////////////////////////////////////////////////
class ApplicationAppTest : public Application
{
public:
    ApplicationAppTest(Engine &engine);
    virtual ~ApplicationAppTest() override;

    int runTests();
};
////////////////////////////////////////////////////////////////////////////////
#endif // __APPTEST_HPP__
