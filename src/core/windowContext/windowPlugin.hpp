#ifndef __WINDOWPLUGIN_HPP__
#define __WINDOWPLUGIN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class WindowPlugin : public Library
{
public:
    WindowPlugin(Engine& engine)
        : Library(engine)
    {
    }

    virtual ~WindowPlugin() override
    {
    }

    virtual void swapBuffers()
    {}
};
////////////////////////////////////////////////////////////////////////////////
#endif // __WINDOWCONTEXT_HPP__
