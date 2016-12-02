////////////////////////////////////////////////////////////////////////////////
#include "inputSDLDeviceJoystick.hpp"
////////////////////////////////////////////////////////////////////////////////
InputSDLDeviceJoystick::InputSDLDeviceJoystick()
{
}
////////////////////////////////////////////////////////////////////////////////
InputSDLDeviceJoystick::~InputSDLDeviceJoystick()
{
}
////////////////////////////////////////////////////////////////////////////////
bool InputSDLDeviceJoystick::isPressed(Input::Joystick button)
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
void InputSDLDeviceJoystick::update()
{
    super::update();
}
////////////////////////////////////////////////////////////////////////////////
void InputSDLDeviceJoystick::update(SDL_Event* event)
{

}
////////////////////////////////////////////////////////////////////////////////
float InputSDLDeviceJoystick::value(Input::Joystick axis)
{
    return 0.0f;
}
////////////////////////////////////////////////////////////////////////////////
size_t InputSDLDeviceJoystick::getMemSize() const
{
    return super::getMemSize();
}
////////////////////////////////////////////////////////////////////////////////
void InputSDLDeviceJoystick::printOn(Logger& o) const
{

}
////////////////////////////////////////////////////////////////////////////////
