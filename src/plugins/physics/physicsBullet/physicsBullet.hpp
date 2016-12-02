#ifndef __PHYSICSBULLET_HPP__
#define __PHYSICSBULLET_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "physicsbullet_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" PHYSICSBULLET_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" PHYSICSBULLET_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" PHYSICSBULLET_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginPhysicsBullet : public Library
{
public:
    PluginPhysicsBullet(Engine& engine);
    ~PluginPhysicsBullet();
};
////////////////////////////////////////////////////////////////////////////////
#endif // __PHYSICSBULLET_HPP__
