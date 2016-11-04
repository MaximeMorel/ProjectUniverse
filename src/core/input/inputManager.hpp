#ifndef __INPUTMANAGER_HPP__
#define __INPUTMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "inputDevice.hpp"
#include "inputDeviceKeyboard.hpp"
#include "inputDeviceMouse.hpp"
#include "inputDeviceJoystick.hpp"
#include "inputDeviceTouchscreen.hpp"
#include "core/log/logger.hpp"
#include <vector>
////////////////////////////////////////////////////////////////////////////////
class InputManager
{
public:
    InputManager();
    ~InputManager();

    void discoverDevices();
    void listDevices() const;

    void update();

    InputDeviceKeyboard& keyboard(size_t id);
    InputDeviceMouse& mouse(size_t id);
    InputDeviceJoystick& joystick(size_t id);
    InputDeviceTouchscreen& touchscreen(size_t id);

    //size_t getNumDevices(DeviceTypes dt) const;

    virtual size_t getMemSize() const;

    virtual void printOn(Logger& o) const;

    enum class DeviceTypes
    {
        KEYBOARD,
        MOUSE,
        JOYSTICK,
        TOUCHSCREEN
    };
    size_t getNumDevices(DeviceTypes dt) const;

private:
    std::vector<InputDeviceKeyboard> m_keyboard;
    std::vector<InputDeviceMouse> m_mouse;
    std::vector<InputDeviceJoystick> m_joystick;
    std::vector<InputDeviceTouchscreen> m_touchscreen;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTMANAGER_HPP__
