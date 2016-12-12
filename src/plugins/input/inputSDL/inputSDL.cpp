////////////////////////////////////////////////////////////////////////////////
#include "inputSDL.hpp"
#include "core/log/logManager.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "inputSDL",
                          "inputSDL",
                          "input",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginInputSDL* lib = nullptr;
////////////////////////////////////////////////////////////////////////////////
const PluginInfo* getPluginInfo()
{
    return &pluginInfo;
}
////////////////////////////////////////////////////////////////////////////////
Library* getLibInstance(Engine* engine)
{
    if (lib == nullptr)
    {
        lib = new PluginInputSDL(*engine);
    }
    return lib;
}
////////////////////////////////////////////////////////////////////////////////
void closeLibInstance()
{
    delete lib;
    lib = nullptr;
}
////////////////////////////////////////////////////////////////////////////////
PluginInputSDL::PluginInputSDL(Engine &engine)
    : InputPlugin(engine)
{
    log().log() << "PluginInputSDL start...\n";

    int ret = SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
    if (ret < 0)
    {
        log().log() << SDL_GetError();
    }
    else if (ret == 0)
    {
        log().log() << "SDL_INIT_GAMECONTROLLER success.\n";
    }

    ret = SDL_InitSubSystem(SDL_INIT_EVENTS);
    if (ret < 0)
    {
        log().log() << SDL_GetError();
    }
    else if (ret == 0)
    {
        log().log() << "SDL_INIT_EVENTS success.\n";
    }
}
////////////////////////////////////////////////////////////////////////////////
PluginInputSDL::~PluginInputSDL()
{
    log().log() << "PluginInputSDL stop...\n";

    SDL_QuitSubSystem(SDL_INIT_EVENTS);
    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
    SDL_Quit();
}
////////////////////////////////////////////////////////////////////////////////
void PluginInputSDL::discoverDevices()
{
    m_keyboard.emplace_back(InputSDLDeviceKeyboard());
    m_mouse.emplace_back(InputSDLDeviceMouse());
}
////////////////////////////////////////////////////////////////////////////////
size_t PluginInputSDL::getNumDevices(Input::DeviceType dt)
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
InputDevice* PluginInputSDL::getDevice(Input::DeviceType dt, size_t deviceId)
{
    if (deviceId >= getNumDevices(dt))
        return nullptr;

    switch (dt)
    {
        case Input::DeviceType::KEYBOARD:
            return &m_keyboard[deviceId];
        case Input::DeviceType::MOUSE:
            return &m_mouse[deviceId];
        case Input::DeviceType::JOYSTICK:
            return &m_joystick[deviceId];
        case Input::DeviceType::TOUCHSCREEN:
            return &m_touchscreen[deviceId];
    }
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
void PluginInputSDL::update()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        for (auto& device : m_keyboard)
        {
            device.update(&event);
        }
        for (auto device : m_mouse)
        {
            device.update(&event);
        }
        for (auto device : m_joystick)
        {
            device.update(&event);
        }
        for (auto device : m_touchscreen)
        {
            device.update(&event);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
size_t PluginInputSDL::getMemSize() const
{
    return m_keyboard.size() * sizeof(InputSDLDeviceKeyboard) +
           m_mouse.size() * sizeof(InputSDLDeviceMouse) +
           m_joystick.size() * sizeof(InputSDLDeviceJoystick) +
           m_touchscreen.size() * sizeof(InputSDLDeviceTouchscreen);
}
////////////////////////////////////////////////////////////////////////////////
void PluginInputSDL::printOn(Logger& o) const
{

}
////////////////////////////////////////////////////////////////////////////////
