#ifndef __INPUTMANAGER_HPP__
#define __INPUTMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "inputDevice.hpp"
#include "inputDeviceKeyboard.hpp"
#include "inputDeviceMouse.hpp"
#include "inputDeviceJoystick.hpp"
#include "inputDeviceTouchscreen.hpp"
#include "core/plugin/plugin.hpp"
#include "core/log/logger.hpp"
#include "core/engine_export.h"
#include <vector>
////////////////////////////////////////////////////////////////////////////////
class InputPlugin;
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT InputManager
{
public:
    InputManager();
    ~InputManager();

    bool setPlugin(PluginLibPtr inputPlugin);

    void discoverDevices();
    void listDevices(Logger& o) const;

    void update();

    InputDeviceKeyboard* keyboard(size_t id);
    InputDeviceMouse* mouse(size_t id);
    InputDeviceJoystick* joystick(size_t id);
    InputDeviceTouchscreen* touchscreen(size_t id);

    InputDevice& getDevice(Input::DeviceType dt, size_t id);
    size_t getNumDevices(Input::DeviceType dt) const;

    void setWindowInputFocus(uint32_t windowId);

    virtual size_t getMemSize() const;

    virtual void printOn(Logger& o) const;

private:
    InputPlugin* m_plugin;

    std::vector<InputDeviceKeyboard*> m_keyboard;        ///< keyboard devices
    std::vector<InputDeviceMouse*> m_mouse;              ///< mouce devices
    std::vector<InputDeviceJoystick*> m_joystick;        ///< joystick devices
    std::vector<InputDeviceTouchscreen*> m_touchscreen;  ///< touchscreen devices
};
////////////////////////////////////////////////////////////////////////////////
/// Global input access
void setGlobalInput(InputManager& input);
InputManager ENGINE_EXPORT & input();
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTMANAGER_HPP__
