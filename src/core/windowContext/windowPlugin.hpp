#ifndef __WINDOWPLUGIN_HPP__
#define __WINDOWPLUGIN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/log/logger.hpp"
#include "core/math/vec2.hpp"
#include "core/render/renderPlugin.hpp"
////////////////////////////////////////////////////////////////////////////////
class WindowPlugin : public Library
{
public:
    WindowPlugin(Engine& engine);
    virtual ~WindowPlugin() override;

    /// Process window events
    virtual void update();

    virtual bool setResolution(uint32_t x, uint32_t y);

    virtual bool setPosition(uint32_t x, uint32_t y);

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

protected:
    std::string m_title;        ///< window title
    bool m_borderless;          ///< borderless window flag
    bool m_fullscreen;          ///< fullscreen window flag
    Vec2i m_resolution;         ///< window resolution
    Vec2i m_position;           ///< window position
};
////////////////////////////////////////////////////////////////////////////////
#endif // __WINDOWCONTEXT_HPP__
