#ifndef __RENDERVULKAN_HPP__
#define __RENDERVULKAN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/render/renderPlugin.hpp"
#include "vulkan/vulkan.h"
#include "rendervulkan_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDERVULKAN_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDERVULKAN_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDERVULKAN_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginRenderVulkan : public RenderPlugin
{
public:
    PluginRenderVulkan(Engine& engine);
    virtual ~PluginRenderVulkan() override;

    virtual bool init() override;

    virtual const char* getShaderSearchPath() const override;
    virtual GfxContextType getRequiredContextType() const override;

private:
    VkApplicationInfo m_applicationInfo;
    VkInstanceCreateInfo m_instanceInfo;
    VkInstance m_instance;

    // flags
    int m_instanceIsValid:1;    ///< instance validity flag
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDERVULKAN_HPP__
