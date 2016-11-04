#ifndef __INPUTSDLDEVICEJOYSTICK_HPP__
#define __INPUTSDLDEVICEJOYSTICK_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/input/inputDeviceJoystick.hpp"
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class InputSDLDeviceJoystick : public InputDeviceJoystick
{
public:
    InputSDLDeviceJoystick();
    virtual ~InputSDLDeviceJoystick();

    virtual void update() override;

    bool isPressed(Input::Joystick button);
    float value(Input::Joystick axis);

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    using super = InputDeviceJoystick;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTSDLDEVICEJOYSTICK_HPP__
