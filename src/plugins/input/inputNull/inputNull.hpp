#ifndef __INPUTNULL_HPP__
#define __INPUTNULL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/input/inputPlugin.hpp"
////////////////////////////////////////////////////////////////////////////////
extern "C" const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginInputNull : public InputPlugin
{
public:
    PluginInputNull(Engine& engine);
    ~PluginInputNull();
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTNULL_HPP__
