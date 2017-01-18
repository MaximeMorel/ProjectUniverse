#ifndef __INPUTDEVICEMOUSE_HPP__
#define __INPUTDEVICEMOUSE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "inputDevice.hpp"
#include "core/log/logger.hpp"
#include "core/math/vec2.hpp"
////////////////////////////////////////////////////////////////////////////////
namespace Input
{
enum Mouse : uint8_t
{
    BT_1 = 0,
    BT_2,
    BT_3,
    BT_4,
    BT_5,
    BT_6,
    BT_7,
    BT_8,
    BT_9,
    BT_10,

    BT_WHEEL_UP,
    BT_WHEEL_DOWN,

    BT_NONE,

    NB_BUTTONS
};
enum class ButtonMode : uint8_t
{
    UP = 0,
    DOWN,
    DOWN_ONCE
};
} // namespace Input
////////////////////////////////////////////////////////////////////////////////
class InputDeviceMouse : public InputDevice
{
public:
    InputDeviceMouse();
    virtual ~InputDeviceMouse();

    virtual void preUpdate() override;
    virtual void update() override;

    bool isPressed(Input::Mouse button);
    bool isPressedOnce(Input::Mouse button);

    bool isMotion(Vec2i& coords);
    bool isRelativeMotion(Vec2i& relCoords);

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

protected:
    void set(Input::Mouse button, Input::ButtonMode mode);

private:
    using super = InputDevice;

protected:
    Input::ButtonMode m_buttons[Input::Mouse::NB_BUTTONS];
    Vec2i m_mouseCoords;
    Vec2i m_mouseRelCoords;
    bool m_hasMotion;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTDEVICEMOUSE_HPP__
