////////////////////////////////////////////////////////////////////////////////
#include "engine.hpp"
#include "application.hpp"
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
void processArgs(int argc, char **argv)
{
    for (int i = 0; i < argc; ++i)
    {

    }
}
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    std::cout << "Start...\n";
    Engine engine("main");

    PluginAppPtr app = res().createFromFile<PluginApp>("example/libexample.so");
    if (app && app->isValid())
    {
        engine.log().log() << app << "\n";
        Application* a = app->getLibInstance(&engine);
        if (a)
            a->run();
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
