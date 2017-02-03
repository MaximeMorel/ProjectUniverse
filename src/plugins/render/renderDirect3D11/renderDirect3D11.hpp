#ifndef __RENDERDIRECT3D11_HPP__
#define __RENDERDIRECT3D11_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/render/renderPlugin.hpp"
#include "renderdirect3D11_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDERDIRECT3D11_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDERDIRECT3D11_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDERDIRECT3D11_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginRenderDirect3D11 : public RenderPlugin
{
public:
    PluginRenderDirect3D11(Engine& engine);
    virtual ~PluginRenderDirect3D11() override;

    virtual bool init() override;

    virtual const char* getShaderSearchPath() const override;
    virtual GfxContextType getRequiredContextType() const override;

private:
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDERDIRECT3D11_HPP__
