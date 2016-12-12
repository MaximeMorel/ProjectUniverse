#ifndef __WINDOWCONTEXTXLIB_HPP__
#define __WINDOWCONTEXTXLIB_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/windowContext/windowContext.hpp"
#include "core/library.hpp"
////////////////////////////////////////////////////////////////////////////////
extern "C" const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginWindowContextXlib : public Library
{
public:
    PluginWindowContextXlib(Engine &engine);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __WINDOWCONTEXTXLIB_HPP__
