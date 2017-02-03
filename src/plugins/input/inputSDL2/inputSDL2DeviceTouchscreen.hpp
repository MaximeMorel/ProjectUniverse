#ifndef __INPUTSDL2DEVICETOUCHSCREEN_HPP__
#define __INPUTSDL2DEVICETOUCHSCREEN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/input/inputDeviceTouchscreen.hpp"
#include "core/log/logger.hpp"
#include <SDL.h>
////////////////////////////////////////////////////////////////////////////////
class InputSDL2DeviceTouchscreen : public InputDeviceTouchscreen
{
public:
    InputSDL2DeviceTouchscreen();
    virtual ~InputSDL2DeviceTouchscreen();

    virtual void update() override;
    bool update(SDL_Event* event);

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    using super = InputDeviceTouchscreen;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTSDL2DEVICETOUCHSCREEN_HPP__
