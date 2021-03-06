#ifndef __ENGINE_LUA_HPP__
#define __ENGINE_LUA_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/engine_export.h"
#include <string>
struct lua_State;
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT EngineLua
{
public:
    EngineLua();
    ~EngineLua();

    bool registerEngineLua();

    bool executeFile(const std::string& file);

private:
    lua_State* m_luaState;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __ENGINE_LUA_HPP__
