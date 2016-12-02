#ifndef __APPNULL_HPP__
#define __APPNULL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/application.hpp"
#include "appnull_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" APPNULL_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" APPNULL_EXPORT Application* getAppInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" APPNULL_EXPORT void closeAppInstance();
////////////////////////////////////////////////////////////////////////////////
class ApplicationAppNull : public Application
{
public:
    ApplicationAppNull(Engine& engine);
    virtual ~ApplicationAppNull() override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __APPNULL_HPP__
