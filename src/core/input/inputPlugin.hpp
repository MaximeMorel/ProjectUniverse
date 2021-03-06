#ifndef __INPUTPLUGIN_HPP__
#define __INPUTPLUGIN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/input/inputDevice.hpp"
#include "core/log/logger.hpp"
#include "core/engine_export.h"
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT InputPlugin : public Library
{
public:
    InputPlugin(Engine& engine);
    virtual ~InputPlugin() override;

    virtual void discoverDevices();
    virtual size_t getNumDevices(Input::DeviceType dt);
    virtual InputDevice* getDevice(Input::DeviceType dt, size_t deviceId);

    virtual void setWindowInputFocus(uint32_t windowId);

    virtual void update();

    virtual size_t getMemSize() const;

    virtual void printOn(Logger& o) const;

private:

};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTPLUGIN_HPP__
