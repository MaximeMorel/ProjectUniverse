#ifndef __RENDERNULL_HPP__
#define __RENDERNULL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "rendernull_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDERNULL_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDERNULL_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" RENDERNULL_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginRenderNull : public Library
{
public:
    PluginRenderNull(Engine& engine);
    virtual ~PluginRenderNull() override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RENDERNULL_HPP__
