#ifndef __RENDERVULKAN_HPP__
#define __RENDERVULKAN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "vulkan/vulkan.h"
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

private:
    vkApplicationInfo m_applicationInfo;
    vkInstanceCreateInfo m_instanceInfo;
    vkInstance m_instance;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDERVULKAN_HPP__
