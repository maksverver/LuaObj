#ifndef LUA_OBJ_H_INCLUDED
#define LUA_OBJ_H_INCLUDED

#include <lua.hpp>
#include <vector>
#include <string>
#include <map>

template<class T> int push_res(lua_State *L, T const &val);
#include "results.inc.cpp"

template<class T> T get_arg(lua_State *L, int idx);
#include "arguments.inc.cpp"

class LuaMethodBase
{
public:
    virtual ~LuaMethodBase() { };
    virtual int invoke(lua_State *L, void *obj) = 0;
};
#include "methods.inc.cpp"


class LuaObj
{
    typedef std::map<std::string, LuaMethodBase *> MethodMap;
    MethodMap methods;

protected:
    virtual ~LuaObj();
    void add_method(const std::string &name, LuaMethodBase *method);

public:
    LuaObj(lua_State *L);
    LuaMethodBase *get_method(const std::string &name) const;
};

#endif /* ndef LUA_OBJ_H_INCLUDED */

