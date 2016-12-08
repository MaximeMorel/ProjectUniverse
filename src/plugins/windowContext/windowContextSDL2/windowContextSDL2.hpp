#ifndef __WINDOWCONTEXTSDL2_HPP__
#define __WINDOWCONTEXTSDL2_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/log/logger.hpp"
#include "core/windowContext/windowPlugin.hpp"
#include <SDL.h>
#include "windowcontextsdl2_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" WINDOWCONTEXTSDL2_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" WINDOWCONTEXTSDL2_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" WINDOWCONTEXTSDL2_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginWindowContextSDL2 : public WindowPlugin
{
public:
    PluginWindowContextSDL2(Engine& Engine);
    virtual ~PluginWindowContextSDL2() override;

    virtual bool setResolution(Vec2i resolution) override;

    virtual bool setPosition(Vec2i position) override;

    virtual bool setTitle(const std::string& title) override;

    virtual void swapBuffers() override;

private:
    void checkAttributes();

private:
    SDL_Window* m_window;
    SDL_GLContext m_glcontext;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __WINDOWCONTEXTSDL2_HPP__
