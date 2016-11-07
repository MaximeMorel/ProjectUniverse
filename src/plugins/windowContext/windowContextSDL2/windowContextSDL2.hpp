#ifndef __WINDOWCONTEXTSDL2_HPP__
#define __WINDOWCONTEXTSDL2_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/windowContext/windowPlugin.hpp"
////////////////////////////////////////////////////////////////////////////////
extern "C" const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginWindowContextSDL2 : public WindowPlugin
{
public:
    PluginWindowContextSDL2(Engine& Engine);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __WINDOWCONTEXTSDL2_HPP__
