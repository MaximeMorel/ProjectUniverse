#ifndef __WINDOWPLUGIN_HPP__
#define __WINDOWPLUGIN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/log/logger.hpp"
#include "core/math/vec2.hpp"
#include <functional>
////////////////////////////////////////////////////////////////////////////////
enum class GfxContextType : int8_t
{
    OPENGL_2_0,
    OPENGL_3_3,
    OPENGL_4_5,
    VULKAN,
    NONE
};
////////////////////////////////////////////////////////////////////////////////
/// \brief The WindowPlugin class
/// Window and graphic context creation
class WindowPlugin : public Library
{
public:
    WindowPlugin(Engine& engine);
    virtual ~WindowPlugin() override;

    virtual bool createContext(GfxContextType type);

    /// Process window events like resize, window close
    virtual void update();

    virtual bool setResolution(uint32_t x, uint32_t y);

    virtual bool setPosition(uint32_t x, uint32_t y);

    virtual bool setFullscreenMode(bool mode);

    virtual bool setBorderlessMode(bool mode);

    virtual bool setTitle(const std::string& title);

    const std::string& getTitle() const;

    virtual void swapBuffers();

    virtual uint32_t getWindowId() const;

    void setEventResizeCallback(const std::function<void(uint32_t, uint32_t)>& func);
    void setEventCloseCallback(const std::function<void()>& func);

protected:
    std::string m_title;            ///< window title
    GfxContextType m_contextType;   ///< context type
    bool m_borderless;              ///< borderless window flag
    bool m_fullscreen;              ///< fullscreen window flag
    Vec2ui m_resolution;            ///< window resolution
    Vec2ui m_position;              ///< window position
    std::function<void(uint32_t, uint32_t)> m_resizeCallback;   ///< resize event callbacks
    std::function<void()> m_closeCallback;                      ///< close event callbacks
};
////////////////////////////////////////////////////////////////////////////////
#endif // __WINDOWCONTEXT_HPP__
