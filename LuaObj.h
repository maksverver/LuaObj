#ifndef LUA_OBJ_H_INCLUDED
#define LUA_OBJ_H_INCLUDED

#include <lua.hpp>
#include <vector>
#include <string>
#include <map>

class LuaObj;

template<class T> int push_res(lua_State *L, T const &val);
template<class T> T get_arg(lua_State *L, int idx);

class LuaMethodBase
{
public:
    virtual ~LuaMethodBase() { };
    virtual int invoke(lua_State *L, void *obj) = 0;
};


class LuaObj
{
    typedef std::map<std::string, LuaMethodBase *> MethodMap;
    MethodMap methods;
    int refcount;

protected:
    virtual ~LuaObj();
    void add_method(const std::string &name, LuaMethodBase *method);

public:
    LuaObj();
    LuaMethodBase *get_method(const std::string &name) const;
    void push(lua_State *L);
    void deref();
};

#include "results.inc.cpp"
#include "arguments.inc.cpp"
#include "methods.inc.cpp"

#endif /* ndef LUA_OBJ_H_INCLUDED */

