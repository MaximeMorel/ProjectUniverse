#ifndef __INPUTDEVICETOUCHSCREEN_HPP__
#define __INPUTDEVICETOUCHSCREEN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "inputDevice.hpp"
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class InputDeviceTouchscreen : public InputDevice
{
public:
    InputDeviceTouchscreen();
    virtual ~InputDeviceTouchscreen();

    virtual void preUpdate() override;
    virtual void update() override;

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    using super = InputDevice;
};
////////////////////////////////////////////////////////////////////////////////
namespace Input
{
enum class TOUCHSCREEN
{
    TOUCH_1
};
} // namespace Input
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTDEVICETOUCHSCREEN_HPP__
