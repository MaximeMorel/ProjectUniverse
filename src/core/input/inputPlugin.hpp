#ifndef __INPUTPLUGIN_HPP__
#define __INPUTPLUGIN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/input/inputDevice.hpp"
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class InputPlugin : public Library
{
public:
    InputPlugin(Engine& engine);
    virtual ~InputPlugin();

    virtual void discoverDevices();

    virtual size_t getNumDevices(Input::DeviceType dt);
    virtual InputDevice* getDevice(Input::DeviceType dt, size_t deviceId);

    virtual void update();

    virtual size_t getMemSize() const;

    virtual void printOn(Logger& o) const;

private:

};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTPLUGIN_HPP__
