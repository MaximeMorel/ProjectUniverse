#ifndef __WINDOWPLUGIN_HPP__
#define __WINDOWPLUGIN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/log/logger.hpp"
#include "core/math/vec2.hpp"
////////////////////////////////////////////////////////////////////////////////
class WindowPlugin : public Library
{
public:
    WindowPlugin(Engine& engine)
        : Library(engine)
        , m_title("main")
        , m_borderless(false)
        , m_fullscreen(false)
        , m_resolution(800, 600)
    {
    }

    virtual ~WindowPlugin() override
    {
    }

    virtual bool setResolution(Vec2i resolution)
    {
        m_resolution = resolution;
        return true;
    }

    virtual bool setPosition(Vec2i position)
    {
        return true;
    }

    virtual bool setFullscreenMode(bool mode)
    {
        m_fullscreen = mode;
        return true;
    }

    virtual bool setBorderlessMode(bool mode)
    {
        m_borderless = mode;
        return true;
    }

    virtual bool setTitle(const std::string& title)
    {
        m_title = title;
        return true;
    }

    const std::string& getTitle() const
    {
        return m_title;
    }

    virtual void swapBuffers()
    {}

private:
    std::string m_title;        ///< window title
    bool m_borderless;          ///< borderless window flag
    bool m_fullscreen;          ///< fullscreen window flag
    Vec2i m_resolution;         ///< window resolution
};
////////////////////////////////////////////////////////////////////////////////
#endif // __WINDOWCONTEXT_HPP__
