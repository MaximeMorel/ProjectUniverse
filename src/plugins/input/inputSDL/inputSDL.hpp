#ifndef __INPUTSDL_HPP__
#define __INPUTSDL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
////////////////////////////////////////////////////////////////////////////////
extern "C" const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginInputSDL : public Library
{
public:
    PluginInputSDL(Engine& engine);
    ~PluginInputSDL();
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTSDL_HPP__
