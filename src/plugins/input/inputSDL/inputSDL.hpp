#ifndef __INPUTSDL_HPP__
#define __INPUTSDL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/input/inputPlugin.hpp"
#include "inputSDLDeviceKeyboard.hpp"
#include "inputSDLDeviceMouse.hpp"
#include "inputSDLDeviceJoystick.hpp"
#include "inputSDLDeviceTouchscreen.hpp"
#include "inputsdl_export.h"
#include <vector>
////////////////////////////////////////////////////////////////////////////////
extern "C" INPUTSDL_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" INPUTSDL_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" INPUTSDL_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginInputSDL : public InputPlugin
{
public:
    PluginInputSDL(Engine& engine);
    virtual ~PluginInputSDL() override;

    virtual void discoverDevices() override;
    virtual size_t getNumDevices(Input::DeviceType dt) override;
    virtual InputDevice *getDevice(Input::DeviceType dt, size_t deviceId) override;

    virtual void update() override;

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    std::vector<InputSDLDeviceKeyboard> m_keyboard;
    std::vector<InputSDLDeviceMouse> m_mouse;
    std::vector<InputSDLDeviceJoystick> m_joystick;
    std::vector<InputSDLDeviceTouchscreen> m_touchscreen;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTSDL_HPP__
