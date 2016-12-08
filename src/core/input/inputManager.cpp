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
void InputManager::setPlugin(PluginLibPtr inputPlugin)
{
    if (m_plugin)
    {
        // clean current plugin
        getEngine().log().log() << "Removing current Input Plugin\n";
    }
    const PluginInfo& pluginInfo = inputPlugin->getInfo();
    if (pluginInfo.type == std::string("input"))
    {
        InputPlugin* plugin = static_cast<InputPlugin*>(inputPlugin->getLibInstance(&getEngine()));
        m_plugin = plugin;

        getEngine().log().log() << "Input Plugin set\n";
    }
    else
    {
        getEngine().log().log() << "Wrong Input Plugin\n";
    }
}
////////////////////////////////////////////////////////////////////////////////
void InputManager::discoverDevices()
{
    m_plugin->discoverDevices();

    size_t n = m_plugin->getNumDevices(Input::DeviceType::KEYBOARD);
    m_keyboard.clear();
    for (size_t i = 0; i < n; ++i)
    {
        m_keyboard.push_back(static_cast<InputDeviceKeyboard*>(m_plugin->getDevice(Input::DeviceType::KEYBOARD, i)));
    }

    n = m_plugin->getNumDevices(Input::DeviceType::MOUSE);
    m_mouse.clear();
    for (size_t i = 0; i < n; ++i)
    {
        m_mouse.push_back(static_cast<InputDeviceMouse*>(m_plugin->getDevice(Input::DeviceType::MOUSE, i)));
    }

    n = m_plugin->getNumDevices(Input::DeviceType::JOYSTICK);
    m_joystick.clear();
    for (size_t i = 0; i < n; ++i)
    {
        m_joystick.push_back(static_cast<InputDeviceJoystick*>(m_plugin->getDevice(Input::DeviceType::JOYSTICK, i)));
    }

    n = m_plugin->getNumDevices(Input::DeviceType::TOUCHSCREEN);
    m_touchscreen.clear();
    for (size_t i = 0; i < n; ++i)
    {
        m_touchscreen.push_back(static_cast<InputDeviceTouchscreen*>(m_plugin->getDevice(Input::DeviceType::TOUCHSCREEN, i)));
    }
}
////////////////////////////////////////////////////////////////////////////////
void InputManager::listDevices(Logger &o) const
{
    for (const auto* device : m_keyboard)
    {
        o << *device << "\n";
    }
    for (const auto* device : m_mouse)
    {
        o << *device << "\n";
    }
    for (const auto* device : m_joystick)
    {
        o << *device << "\n";
    }
    for (const auto* device : m_touchscreen)
    {
        o << *device << "\n";
    }
}
////////////////////////////////////////////////////////////////////////////////
void InputManager::update()
{
    m_plugin->update();
}
////////////////////////////////////////////////////////////////////////////////
InputDeviceKeyboard* InputManager::keyboard(size_t id)
{
    if (id < m_keyboard.size())
        return m_keyboard[id];
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
InputDeviceMouse* InputManager::mouse(size_t id)
{
    if (id < m_mouse.size())
        return m_mouse[id];
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
InputDeviceJoystick* InputManager::joystick(size_t id)
{
    if (id < m_joystick.size())
        return m_joystick[id];
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
InputDeviceTouchscreen* InputManager::touchscreen(size_t id)
{
    if (id < m_touchscreen.size())
        return m_touchscreen[id];
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
InputDevice& InputManager::getDevice(Input::DeviceType dt, size_t id)
{
    switch (dt)
    {
    case Input::DeviceType::KEYBOARD:
        return *m_keyboard[id];
    case Input::DeviceType::MOUSE:
        return *m_mouse[id];
    case Input::DeviceType::JOYSTICK:
        return *m_joystick[id];
    case Input::DeviceType::TOUCHSCREEN:
        return *m_touchscreen[id];
    }
    return *m_keyboard[0];
}
////////////////////////////////////////////////////////////////////////////////
size_t InputManager::getNumDevices(Input::DeviceType dt) const
{
    switch (dt)
    {
    case Input::DeviceType::KEYBOARD:
        return m_keyboard.size();
    case Input::DeviceType::MOUSE:
        return m_mouse.size();
    case Input::DeviceType::JOYSTICK:
        return m_joystick.size();
    case Input::DeviceType::TOUCHSCREEN:
        return m_touchscreen.size();
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
size_t InputManager::getMemSize() const
{
    return m_keyboard.size() * sizeof(InputDeviceKeyboard*) +
           m_mouse.size() * sizeof(InputDeviceMouse*) +
           m_joystick.size() * sizeof(InputDeviceJoystick*) +
           m_touchscreen.size() * sizeof(InputDeviceTouchscreen*);
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
