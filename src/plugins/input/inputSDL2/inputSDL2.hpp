#ifndef __INPUTSDL2_HPP__
#define __INPUTSDL2_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/input/inputPlugin.hpp"
#include "inputSDL2DeviceKeyboard.hpp"
#include "inputSDL2DeviceMouse.hpp"
#include "inputSDL2DeviceJoystick.hpp"
#include "inputSDL2DeviceTouchscreen.hpp"
#include "inputsdl2_export.h"
#include <vector>
////////////////////////////////////////////////////////////////////////////////
extern "C" INPUTSDL2_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" INPUTSDL2_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" INPUTSDL2_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginInputSDL2 : public InputPlugin
{
public:
    PluginInputSDL2(Engine& engine);
    virtual ~PluginInputSDL2() override;

    virtual void discoverDevices() override;
    virtual size_t getNumDevices(Input::DeviceType dt) override;
    virtual InputDevice *getDevice(Input::DeviceType dt, size_t deviceId) override;

    virtual void setWindowInputFocus(uint32_t windowId) override;

    virtual void update() override;

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    std::vector<InputSDL2DeviceKeyboard> m_keyboard;
    std::vector<InputSDL2DeviceMouse> m_mouse;
    std::vector<InputSDL2DeviceJoystick> m_joystick;
    std::vector<InputSDL2DeviceTouchscreen> m_touchscreen;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTSDL2_HPP__
