////////////////////////////////////////////////////////////////////////////////
#include "inputDevice.hpp"
////////////////////////////////////////////////////////////////////////////////
InputDevice::InputDevice()
{
}
////////////////////////////////////////////////////////////////////////////////
InputDevice::~InputDevice()
{
}
////////////////////////////////////////////////////////////////////////////////
void InputDevice::preUpdate()
{
}
////////////////////////////////////////////////////////////////////////////////
void InputDevice::update()
{
}
////////////////////////////////////////////////////////////////////////////////
size_t InputDevice::getMemSize() const
{
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
void InputDevice::printOn(Logger& o) const
{

}
////////////////////////////////////////////////////////////////////////////////
Logger& operator<<(Logger& o, const InputDevice& dev)
{
    dev.printOn(o);
    return o;
}
////////////////////////////////////////////////////////////////////////////////
