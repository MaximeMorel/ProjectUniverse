////////////////////////////////////////////////////////////////////////////////
#include "inputManager.hpp"
#include "inputPlugin.hpp"
////////////////////////////////////////////////////////////////////////////////
InputManager::InputManager()
    : m_plugin(nullptr)
{
}
////////////////////////////////////////////////////////////////////////////////
InputManager::~InputManager()
{
}
////////////////////////////////////////////////////////////////////////////////
void InputManager::discoverDevices()
{

}
////////////////////////////////////////////////////////////////////////////////
void InputManager::listDevices(Logger &o) const
{

}
////////////////////////////////////////////////////////////////////////////////
void InputManager::update()
{
    for (auto& device : m_keyboard)
    {
        device.update();
    }
    for (auto& device : m_mouse)
    {
        device.update();
    }
    for (auto& device : m_joystick)
    {
        device.update();
    }
    for (auto& device : m_touchscreen)
    {
        device.update();
    }
}
////////////////////////////////////////////////////////////////////////////////
InputDeviceKeyboard& InputManager::keyboard(size_t id)
{
    return m_keyboard[id];
}
////////////////////////////////////////////////////////////////////////////////
InputDeviceMouse& InputManager::mouse(size_t id)
{
    return m_mouse[id];
}
////////////////////////////////////////////////////////////////////////////////
InputDeviceJoystick& InputManager::joystick(size_t id)
{
    return m_joystick[id];
}
////////////////////////////////////////////////////////////////////////////////
InputDeviceTouchscreen& InputManager::touchscreen(size_t id)
{
    return m_touchscreen[id];
}
////////////////////////////////////////////////////////////////////////////////
InputDevice& InputManager::getDevice(DeviceTypes dt, size_t id)
{
    switch(dt)
    {
    case DeviceTypes::KEYBOARD:
        return m_keyboard[id];
    case DeviceTypes::MOUSE:
        return m_mouse[id];
    case DeviceTypes::JOYSTICK:
        return m_joystick[id];
    case DeviceTypes::TOUCHSCREEN:
        return m_touchscreen[id];
    }
    return m_keyboard[0];
}
////////////////////////////////////////////////////////////////////////////////
size_t InputManager::getNumDevices(DeviceTypes dt) const
{
    switch(dt)
    {
    case DeviceTypes::KEYBOARD:
        return m_keyboard.size();
    case DeviceTypes::MOUSE:
        return m_mouse.size();
    case DeviceTypes::JOYSTICK:
        return m_joystick.size();
    case DeviceTypes::TOUCHSCREEN:
        return m_touchscreen.size();
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
size_t InputManager::getMemSize() const
{
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
void InputManager::printOn(Logger& o) const
{
    for (auto& device : m_keyboard)
    {
        o << device;
    }
    for (auto& device : m_mouse)
    {
        o << device;
    }
    for (auto& device : m_joystick)
    {
        o << device;
    }
    for (auto& device : m_touchscreen)
    {
        o << device;
    }
}
////////////////////////////////////////////////////////////////////////////////
