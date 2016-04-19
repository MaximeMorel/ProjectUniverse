#ifndef __RENDERVULKAN_HPP__
#define __RENDERVULKAN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
////////////////////////////////////////////////////////////////////////////////
extern "C" const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginRenderVulkan : public Library
{
public:
    PluginRenderVulkan(Engine& engine);
    ~PluginRenderVulkan();
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDERVULKAN_HPP__
