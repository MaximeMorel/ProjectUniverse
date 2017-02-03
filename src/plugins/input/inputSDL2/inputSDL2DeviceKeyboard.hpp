#ifndef __INPUTSDL2DEVICEKEYBOARD_HPP__
#define __INPUTSDL2DEVICEKEYBOARD_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/input/inputDeviceKeyboard.hpp"
#include "core/log/logger.hpp"
#include <SDL.h>
////////////////////////////////////////////////////////////////////////////////
class InputSDL2DeviceKeyboard : public InputDeviceKeyboard
{
public:
    InputSDL2DeviceKeyboard();
    virtual ~InputSDL2DeviceKeyboard();

    virtual void update() override;
    bool update(SDL_Event* event);

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    using super = InputDeviceKeyboard;

    class SDLKeyMapping
    {
    public:
        SDLKeyMapping();
        Input::Keyboard get(SDL_Scancode key);
        Input::Keyboard get(SDL_Keycode key);
    private:
        Input::Keyboard m_mapping[SDL_NUM_SCANCODES];
    };

    SDLKeyMapping m_keyMapping;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTSDL2DEVICEKEYBOARD_HPP__
