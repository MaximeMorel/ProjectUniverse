#ifndef __INPUTSDL2DEVICEJOYSTICK_HPP__
#define __INPUTSDL2DEVICEJOYSTICK_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/input/inputDeviceJoystick.hpp"
#include "core/log/logger.hpp"
#include <SDL.h>
////////////////////////////////////////////////////////////////////////////////
class InputSDL2DeviceJoystick : public InputDeviceJoystick
{
public:
    InputSDL2DeviceJoystick();
    virtual ~InputSDL2DeviceJoystick();

    virtual void update() override;
    bool update(SDL_Event* event);

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    using super = InputDeviceJoystick;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTSDL2DEVICEJOYSTICK_HPP__
