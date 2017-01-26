////////////////////////////////////////////////////////////////////////////////
#include "engine.hpp"
#include "application.hpp"
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    std::cout << "Start...\n";
    Engine engine("main");

    engine.parseArgs(argc, argv);

    PluginAppPtr app = engine.plugins().loadApp();
    if (app && app->isValid() && engine.init())
    {
        engine.log().log() << app << "\n";
        Application* a = app->getLibInstance(&engine);
        if (a)
            a->run();
    }
    engine.log().log() << "main exit..." << std::endl;
    engine.plugins().flushPlugins();
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
