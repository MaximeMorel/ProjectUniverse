#ifndef __INPUTPLUGIN_HPP__
#define __INPUTPLUGIN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class InputPlugin : public Library
{
public:
    InputPlugin(Engine& engine);
    virtual ~InputPlugin();

    virtual void update();

    virtual size_t getMemSize() const;

    virtual void printOn(Logger& o) const;

    friend Logger& operator<<(Logger& o, const InputPlugin& plugin);

private:

};
////////////////////////////////////////////////////////////////////////////////
#endif // __INPUTPLUGIN_HPP__
