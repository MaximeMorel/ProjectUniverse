#ifndef __WINDOWCONTEXTSDL2_HPP__
#define __WINDOWCONTEXTSDL2_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/windowContext/windowPlugin.hpp"
#include <SDL.h>
#include <vector>
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

    virtual bool createContext(GfxContextType type) override;

    virtual void update() override;

    virtual bool setResolution(uint32_t x, uint32_t y) override;

    virtual bool setPosition(uint32_t x, uint32_t y) override;

    virtual bool setTitle(const std::string& title) override;

    virtual void swapBuffers() override;

    virtual uint32_t getWindowId() const override;

private:
    void logAttributes();

    bool createContextOpenGL21();
    bool createContextOpenGL33();
    bool createContextOpenGL45();
    bool createContextVulkan();

    bool createWindow(SDL_WindowFlags flags);

private:
    SDL_Window* m_window;
    SDL_GLContext m_glcontext;
    std::vector<SDL_Event> m_pushedEvents;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __WINDOWCONTEXTSDL2_HPP__
