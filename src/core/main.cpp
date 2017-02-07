////////////////////////////////////////////////////////////////////////////////
#include "engine.hpp"
#include "application.hpp"
#include "core/tools/filetools.hpp"
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    FileTools::chdirGame();

    std::cout << "Start...\n";
    Engine engine("main");

    // get command line parameters first as they have highest priority
    engine.parseArgs(argc, argv);

    PluginAppPtr app = engine.plugins().loadApp();
    if (app && app->isValid() && engine.init(argc, argv))
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
