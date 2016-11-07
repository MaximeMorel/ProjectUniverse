#ifndef __INPUTDEVICE_HPP__
#define __INPUTDEVICE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/log/logger.hpp"
#include <cstdint>
////////////////////////////////////////////////////////////////////////////////
class InputDevice
{
public:
    InputDevice();
    virtual ~InputDevice();

    virtual void update();

    virtual size_t getMemSize() const;

    virtual void printOn(Logger& o) const;

    friend Logger& operator<<(Logger& o, const InputDevice& dev);

private:

};
////////////////////////////////////////////////////////////////////////////////
namespace Input
{
enum class KeyMode : std::int8_t
{
    UP = 0,
    DOWN,
    DOWN_ONCE
};
} // namespace Input
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTDEVICE_HPP__
