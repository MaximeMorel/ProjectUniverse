////////////////////////////////////////////////////////////////////////////////
#include "inputDeviceMouse.hpp"
////////////////////////////////////////////////////////////////////////////////
InputDeviceMouse::InputDeviceMouse()
    : m_hasMotion(false)
{
    for (size_t i = 0; i < Input::Mouse::NB_BUTTONS; ++i)
    {
        m_buttons[i] = Input::ButtonMode::UP;
    }
}
////////////////////////////////////////////////////////////////////////////////
InputDeviceMouse::~InputDeviceMouse()
{
}
////////////////////////////////////////////////////////////////////////////////
void InputDeviceMouse::preUpdate()
{
    m_hasMotion = false;
}
////////////////////////////////////////////////////////////////////////////////
void InputDeviceMouse::update()
{
}
////////////////////////////////////////////////////////////////////////////////
bool InputDeviceMouse::isPressed(Input::Mouse button)
{
    return m_buttons[button] == Input::ButtonMode::DOWN || m_buttons[button] == Input::ButtonMode::DOWN_ONCE;
}
////////////////////////////////////////////////////////////////////////////////
bool InputDeviceMouse::isPressedOnce(Input::Mouse button)
{
    bool ret = false;
    if(m_buttons[button] == Input::ButtonMode::DOWN_ONCE)
    {
        m_buttons[button] = Input::ButtonMode::DOWN;
        ret = true;
    }
    return ret;
}
////////////////////////////////////////////////////////////////////////////////
bool InputDeviceMouse::isMotion(Vec2i& pos)
{
    if (m_hasMotion)
        pos = m_mouseCoords;
    return m_hasMotion;
}
////////////////////////////////////////////////////////////////////////////////
bool InputDeviceMouse::isRelativeMotion(Vec2i& relPos)
{
    if (m_hasMotion)
        relPos = m_mouseRelCoords;
    return m_hasMotion;
}
////////////////////////////////////////////////////////////////////////////////
void InputDeviceMouse::set(Input::Mouse button, Input::ButtonMode mode)
{
    m_buttons[button] = mode;
}
////////////////////////////////////////////////////////////////////////////////
size_t InputDeviceMouse::getMemSize() const
{
    return sizeof(*this);
}
////////////////////////////////////////////////////////////////////////////////
void InputDeviceMouse::printOn(Logger& o) const
{

}
////////////////////////////////////////////////////////////////////////////////
