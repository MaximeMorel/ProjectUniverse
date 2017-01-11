////////////////////////////////////////////////////////////////////////////////
#include "inputSDLDeviceMouse.hpp"
////////////////////////////////////////////////////////////////////////////////
InputSDLDeviceMouse::InputSDLDeviceMouse()
{
}
////////////////////////////////////////////////////////////////////////////////
InputSDLDeviceMouse::~InputSDLDeviceMouse()
{
}
////////////////////////////////////////////////////////////////////////////////
void InputSDLDeviceMouse::update()
{
    super::update();

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        update(&event);
    }
}
////////////////////////////////////////////////////////////////////////////////
bool InputSDLDeviceMouse::update(SDL_Event* event)
{
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:
        set(static_cast<Input::Mouse>(event->button.button - 1), Input::ButtonMode::DOWN_ONCE);
        return true;
    case SDL_MOUSEBUTTONUP:
        set(static_cast<Input::Mouse>(event->button.button - 1), Input::ButtonMode::UP);
        return true;
    case SDL_MOUSEMOTION:
        m_mouseCoords.x = event->motion.x;
        m_mouseCoords.y = event->motion.y;
        m_mouseRelCoords.x = event->motion.xrel;
        m_mouseRelCoords.y = event->motion.yrel;
        m_hasMotion = true;
        return true;
    case SDL_MOUSEWHEEL:
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
size_t InputSDLDeviceMouse::getMemSize() const
{
    return super::getMemSize();
}
////////////////////////////////////////////////////////////////////////////////
void InputSDLDeviceMouse::printOn(Logger& o) const
{
    o << "sdl mouse";
}
////////////////////////////////////////////////////////////////////////////////
