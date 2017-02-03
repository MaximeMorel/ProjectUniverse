#ifndef __INPUTSDL2DEVICEMOUSE_HPP__
#define __INPUTSDL2DEVICEMOUSE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/input/inputDeviceMouse.hpp"
#include "core/log/logger.hpp"
#include <SDL.h>
////////////////////////////////////////////////////////////////////////////////
class InputSDL2DeviceMouse : public InputDeviceMouse
{
public:
    InputSDL2DeviceMouse();
    virtual ~InputSDL2DeviceMouse();

    virtual void preUpdate() override;
    virtual void update() override;
    bool update(SDL_Event* event);

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    using super = InputDeviceMouse;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTSDL2DEVICEMOUSE_HPP__
