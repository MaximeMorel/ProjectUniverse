#ifndef __INPUTDEVICEKEYBOARD_HPP__
#define __INPUTDEVICEKEYBOARD_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "inputDevice.hpp"
#include "core/log/logger.hpp"
#include "core/engine_export.h"
////////////////////////////////////////////////////////////////////////////////
namespace Input
{
enum Keyboard
{
    KEY_a = 0,
    KEY_b,
    KEY_c,
    KEY_d,
    KEY_e,
    KEY_f,
    KEY_g,
    KEY_h,
    KEY_i,
    KEY_j,
    KEY_k,
    KEY_l,
    KEY_m,
    KEY_n,
    KEY_o,
    KEY_p,
    KEY_q,
    KEY_r,
    KEY_s,
    KEY_t,
    KEY_u,
    KEY_v,
    KEY_w,
    KEY_x,
    KEY_y,
    KEY_z,

    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,

    KEY_KP0,
    KEY_KP1,
    KEY_KP2,
    KEY_KP3,
    KEY_KP4,
    KEY_KP5,
    KEY_KP6,
    KEY_KP7,
    KEY_KP8,
    KEY_KP9,

    KEY_KPENTER,

    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,

    KEY_INSERT,
    KEY_DELETE,
    KEY_HOME,
    KEY_END,
    KEY_PAGEUP,
    KEY_PAGEDOWN,

    KEY_SPACE,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_ENTER,
    KEY_LSHIFT,
    KEY_RSHIFT,
    KEY_LCTRL,
    KEY_RCTRL,
    KEY_LSUPER,
    KEY_RSUPER,
    KEY_ALT,
    KEY_ALTGR,
    KEY_MENU,
    KEY_ESC,

    KEY_NONE,

    NB_KEYS
};
enum class KeyMode : uint8_t
{
    UP = 0,
    DOWN,
    DOWN_ONCE
};
} // namespace Input
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT InputDeviceKeyboard : public InputDevice
{
public:
    InputDeviceKeyboard();
    virtual ~InputDeviceKeyboard();

    virtual void preUpdate() override;
    virtual void update() override;

    bool isPressed(Input::Keyboard key);
    bool isPressedOnce(Input::Keyboard key);

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

protected:
    void set(Input::Keyboard key, Input::KeyMode mode);

private:
    using super = InputDevice;
    Input::KeyMode m_keys[Input::Keyboard::NB_KEYS];
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTDEVICEKEYBOARD_HPP__
