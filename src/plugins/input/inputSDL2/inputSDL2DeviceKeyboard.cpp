////////////////////////////////////////////////////////////////////////////////
#include "inputSDL2DeviceKeyboard.hpp"
////////////////////////////////////////////////////////////////////////////////
InputSDL2DeviceKeyboard::InputSDL2DeviceKeyboard()
{
}
////////////////////////////////////////////////////////////////////////////////
InputSDL2DeviceKeyboard::~InputSDL2DeviceKeyboard()
{
}
////////////////////////////////////////////////////////////////////////////////
void InputSDL2DeviceKeyboard::update()
{
    super::update();

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        update(&event);
    }
}
////////////////////////////////////////////////////////////////////////////////
bool InputSDL2DeviceKeyboard::update(SDL_Event* event)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
        set(m_keyMapping.get(event->key.keysym.scancode), Input::KeyMode::DOWN_ONCE);
        return true;
    case SDL_KEYUP:
        set(m_keyMapping.get(event->key.keysym.scancode), Input::KeyMode::UP);
        return true;
    case SDL_KEYMAPCHANGED:
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
size_t InputSDL2DeviceKeyboard::getMemSize() const
{
    return super::getMemSize();
}
////////////////////////////////////////////////////////////////////////////////
void InputSDL2DeviceKeyboard::printOn(Logger& o) const
{
    o << "sdl keyboard";
}
////////////////////////////////////////////////////////////////////////////////
InputSDL2DeviceKeyboard::SDLKeyMapping::SDLKeyMapping()
{
    for (size_t i = 0; i < SDL_NUM_SCANCODES; ++i)
    {
        m_mapping[i] = Input::KEY_NONE;
    }

    m_mapping[SDL_SCANCODE_A] = Input::KEY_a;
    m_mapping[SDL_SCANCODE_B] = Input::KEY_b;
    m_mapping[SDL_SCANCODE_C] = Input::KEY_c;
    m_mapping[SDL_SCANCODE_D] = Input::KEY_d;
    m_mapping[SDL_SCANCODE_E] = Input::KEY_e;
    m_mapping[SDL_SCANCODE_F] = Input::KEY_f;
    m_mapping[SDL_SCANCODE_G] = Input::KEY_g;
    m_mapping[SDL_SCANCODE_H] = Input::KEY_h;
    m_mapping[SDL_SCANCODE_I] = Input::KEY_i;
    m_mapping[SDL_SCANCODE_J] = Input::KEY_j;
    m_mapping[SDL_SCANCODE_K] = Input::KEY_k;
    m_mapping[SDL_SCANCODE_L] = Input::KEY_l;
    m_mapping[SDL_SCANCODE_M] = Input::KEY_m;
    m_mapping[SDL_SCANCODE_N] = Input::KEY_n;
    m_mapping[SDL_SCANCODE_O] = Input::KEY_o;
    m_mapping[SDL_SCANCODE_P] = Input::KEY_p;
    m_mapping[SDL_SCANCODE_Q] = Input::KEY_q;
    m_mapping[SDL_SCANCODE_R] = Input::KEY_r;
    m_mapping[SDL_SCANCODE_S] = Input::KEY_s;
    m_mapping[SDL_SCANCODE_T] = Input::KEY_t;
    m_mapping[SDL_SCANCODE_U] = Input::KEY_u;
    m_mapping[SDL_SCANCODE_V] = Input::KEY_v;
    m_mapping[SDL_SCANCODE_W] = Input::KEY_w;
    m_mapping[SDL_SCANCODE_X] = Input::KEY_x;
    m_mapping[SDL_SCANCODE_Y] = Input::KEY_y;
    m_mapping[SDL_SCANCODE_Z] = Input::KEY_z;

    m_mapping[SDL_SCANCODE_ESCAPE] = Input::KEY_ESC;

}
////////////////////////////////////////////////////////////////////////////////
Input::Keyboard InputSDL2DeviceKeyboard::SDLKeyMapping::get(SDL_Scancode key)
{
    return m_mapping[key];
}
////////////////////////////////////////////////////////////////////////////////
Input::Keyboard InputSDL2DeviceKeyboard::SDLKeyMapping::get(SDL_Keycode key)
{
    return Input::KEY_NONE;
}
////////////////////////////////////////////////////////////////////////////////
