////////////////////////////////////////////////////////////////////////////////
#include "inputSDL2.hpp"
#include "core/log/logManager.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "inputSDL",
                          "inputSDL",
                          "input",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginInputSDL2* lib = nullptr;
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
        lib = new PluginInputSDL2(*engine);
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
PluginInputSDL2::PluginInputSDL2(Engine &engine)
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
PluginInputSDL2::~PluginInputSDL2()
{
    log().log() << "PluginInputSDL stop...\n";

    SDL_QuitSubSystem(SDL_INIT_EVENTS);
    SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
    SDL_Quit();
}
////////////////////////////////////////////////////////////////////////////////
void PluginInputSDL2::discoverDevices()
{
    m_keyboard.emplace_back(InputSDL2DeviceKeyboard());
    m_mouse.emplace_back(InputSDL2DeviceMouse());
}
////////////////////////////////////////////////////////////////////////////////
size_t PluginInputSDL2::getNumDevices(Input::DeviceType dt)
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
InputDevice* PluginInputSDL2::getDevice(Input::DeviceType dt, size_t deviceId)
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
void PluginInputSDL2::setWindowInputFocus(uint32_t windowId)
{
    SDL_Window* window = SDL_CreateWindowFrom(reinterpret_cast<const void*>(windowId));
    //SDL_Window* window = SDL_GetWindowFromID(windowId);
    if (window)
    {
        SDL_RaiseWindow(window);
    }
}
////////////////////////////////////////////////////////////////////////////////
void PluginInputSDL2::update()
{
    for (auto& device : m_keyboard)
    {
        device.preUpdate();
    }
    for (auto& device : m_mouse)
    {
        device.preUpdate();
    }
    for (auto& device : m_joystick)
    {
        device.preUpdate();
    }
    for (auto& device : m_touchscreen)
    {
        device.preUpdate();
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        bool eventConsumed = false;
        for (auto& device : m_keyboard)
        {
            eventConsumed |= device.update(&event);
        }
        if (eventConsumed) continue;
        for (auto& device : m_mouse)
        {
            eventConsumed |= device.update(&event);
        }
        if (eventConsumed) continue;
        for (auto& device : m_joystick)
        {
            eventConsumed |= device.update(&event);
        }
        if (eventConsumed) continue;
        for (auto& device : m_touchscreen)
        {
            eventConsumed |= device.update(&event);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
size_t PluginInputSDL2::getMemSize() const
{
    return m_keyboard.size() * sizeof(InputSDL2DeviceKeyboard) +
           m_mouse.size() * sizeof(InputSDL2DeviceMouse) +
           m_joystick.size() * sizeof(InputSDL2DeviceJoystick) +
           m_touchscreen.size() * sizeof(InputSDL2DeviceTouchscreen);
}
////////////////////////////////////////////////////////////////////////////////
void PluginInputSDL2::printOn(Logger& o) const
{

}
////////////////////////////////////////////////////////////////////////////////
