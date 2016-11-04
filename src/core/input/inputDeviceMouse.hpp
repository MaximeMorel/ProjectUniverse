#ifndef __INPUTDEVICEMOUSE_HPP__
#define __INPUTDEVICEMOUSE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "inputDevice.hpp"
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
namespace Input
{
enum class Mouse
{
    BT_1,
    BT_2,
    BT_3,
    BT_4,
    BT_5,
    BT_6,
    BT_7,
    BT_8,
    BT_9,
    BT_10
};
} // namespace Input
////////////////////////////////////////////////////////////////////////////////
class InputDeviceMouse : public InputDevice
{
public:
    InputDeviceMouse();
    virtual ~InputDeviceMouse();

    virtual void update() override;

    bool isPressed(Input::Mouse button);

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    using super = InputDevice;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTDEVICEMOUSE_HPP__
