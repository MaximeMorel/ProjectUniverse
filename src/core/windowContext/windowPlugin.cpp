////////////////////////////////////////////////////////////////////////////////
#include "windowPlugin.hpp"
#include "core/engine.hpp"
////////////////////////////////////////////////////////////////////////////////
WindowPlugin::WindowPlugin(Engine& engine)
    : Library(engine)
    , m_title("main")
    , m_borderless(false)
    , m_fullscreen(false)
    , m_resolution(800, 600)
{
}
////////////////////////////////////////////////////////////////////////////////
WindowPlugin::~WindowPlugin()
{
}
////////////////////////////////////////////////////////////////////////////////
void WindowPlugin::update()
{
}
////////////////////////////////////////////////////////////////////////////////
bool WindowPlugin::setResolution(uint32_t x, uint32_t y)
{
    m_resolution = Vec2i(x, y);
    getEngine().render().impl()->resize(x, y);
    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool WindowPlugin::setPosition(uint32_t x, uint32_t y)
{
    m_position = Vec2i(x, y);
    return true;
}
////////////////////////////////////////////////////////////////////////////////
