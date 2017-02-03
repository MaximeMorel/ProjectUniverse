////////////////////////////////////////////////////////////////////////////////
#include "inputSDL2DeviceMouse.hpp"
////////////////////////////////////////////////////////////////////////////////
InputSDL2DeviceMouse::InputSDL2DeviceMouse()
{
}
////////////////////////////////////////////////////////////////////////////////
InputSDL2DeviceMouse::~InputSDL2DeviceMouse()
{
}
////////////////////////////////////////////////////////////////////////////////
void InputSDL2DeviceMouse::preUpdate()
{
    super::preUpdate();
    set(Input::Mouse::BT_WHEEL_UP, Input::ButtonMode::UP);
    set(Input::Mouse::BT_WHEEL_DOWN, Input::ButtonMode::UP);
}
////////////////////////////////////////////////////////////////////////////////
void InputSDL2DeviceMouse::update()
{
    super::update();

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        update(&event);
    }
}
////////////////////////////////////////////////////////////////////////////////
bool InputSDL2DeviceMouse::update(SDL_Event* event)
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
        if (event->wheel.y > 0)
            set(Input::Mouse::BT_WHEEL_UP, Input::ButtonMode::DOWN_ONCE);
        else if (event->wheel.y < 0)
            set(Input::Mouse::BT_WHEEL_DOWN, Input::ButtonMode::DOWN_ONCE);
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
size_t InputSDL2DeviceMouse::getMemSize() const
{
    return super::getMemSize();
}
////////////////////////////////////////////////////////////////////////////////
void InputSDL2DeviceMouse::printOn(Logger& o) const
{
    o << "sdl mouse";
}
////////////////////////////////////////////////////////////////////////////////
