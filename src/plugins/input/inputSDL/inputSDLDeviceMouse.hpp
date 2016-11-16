#ifndef __INPUTSDLDEVICEMOUSE_HPP__
#define __INPUTSDLDEVICEMOUSE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/input/inputDeviceMouse.hpp"
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class InputSDLDeviceMouse : public InputDeviceMouse
{
public:
    InputSDLDeviceMouse();
    virtual ~InputSDLDeviceMouse();

    virtual void update() override;

    bool isPressed(Input::Mouse button);

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    using super = InputDeviceMouse;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTSDLDEVICEMOUSE_HPP__