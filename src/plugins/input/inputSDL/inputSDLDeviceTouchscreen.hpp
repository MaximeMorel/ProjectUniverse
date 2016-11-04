#ifndef __INPUTSDLDEVICETOUCHSCREEN_HPP__
#define __INPUTSDLDEVICETOUCHSCREEN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/input/inputDeviceTouchscreen.hpp"
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class InputSDLDeviceTouchscreen : public InputDeviceTouchscreen
{
public:
    InputSDLDeviceTouchscreen();
    virtual ~InputSDLDeviceTouchscreen();

    virtual void update() override;

    virtual size_t getMemSize() const override;

    virtual void printOn(Logger& o) const override;

private:
    using super = InputDeviceTouchscreen;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTSDLDEVICETOUCHSCREEN_HPP__
