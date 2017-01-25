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

    engine.parseArgs(argc, argv);

    PluginAppPtr app = engine.plugins().loadApp("Example");
    if (app && app->isValid())
    {
        engine.log().log() << app << "\n";
        Application* a = app->getLibInstance(&engine);
        if (a)
            a->run();
    }
    engine.log().log() << "main exit..." << std::endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
