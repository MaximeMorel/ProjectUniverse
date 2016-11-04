#ifndef __INPUTSDLDEVICEKEYBOARD_HPP__
#define __INPUTSDLDEVICEKEYBOARD_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/input/inputDeviceKeyboard.hpp"
#include "core/log/logger.hpp"
#include <SDL.h>
////////////////////////////////////////////////////////////////////////////////
class InputSDLDeviceKeyboard : public InputDeviceKeyboard
{
public:
    InputSDLDeviceKeyboard();
    virtual ~InputSDLDeviceKeyboard();

    virtual void update() override;

    bool isPressed(Input::Keyboard key);

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    using super = InputDeviceKeyboard;

    class SDLKeyMapping
    {
    public:
        SDLKeyMapping();
        Input::Keyboard get(SDL_Keycode key);
    private:
        Input::Keyboard m_mapping[SDLK_LALT];
    };
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTSDLDEVICEKEYBOARD_HPP__
