#ifndef __INPUTDEVICEJOYSTICK_HPP__
#define __INPUTDEVICEJOYSTICK_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "inputDevice.hpp"
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
namespace Input
{
enum class Joystick
{
    BT_1,
    AXIS_1
};
} // namespace Input
////////////////////////////////////////////////////////////////////////////////
class InputDeviceJoystick : public InputDevice
{
public:
    InputDeviceJoystick();
    virtual ~InputDeviceJoystick();

    virtual void update() override;

    bool isPressed(Input::Joystick button);
    float value(Input::Joystick axis);

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    using super = InputDevice;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTDEVICEJOYSTICK_HPP__
