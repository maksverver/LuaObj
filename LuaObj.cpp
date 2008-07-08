#include "LuaObj.h"

static int invoke_method(lua_State *L)
{
    LuaObj *obj;
    LuaMethodBase *meth;
    int args;

    args = lua_gettop(L);
    obj  = (LuaObj*)        lua_touserdata(L, lua_upvalueindex(1));
    meth = (LuaMethodBase*) lua_touserdata(L, lua_upvalueindex(2));

    if ( args < 1 || !lua_isuserdata(L, 1) ||
         *(LuaObj**)lua_touserdata(L, 1) != obj )
    {
        lua_pushfstring(L, "invoke_method: missing/incorrect object instance");
        lua_error(L);
    }

    return meth->invoke(L, obj);
}

static int free_object(lua_State *L)
{
    if (lua_gettop(L) < 1 || !lua_isuserdata(L, 1))
    {
        lua_pushfstring(L, "free_object: missing/incorrect object instance");
        lua_error(L);
    }
    LuaObj* obj = *(LuaObj**)lua_touserdata(L, 1);
    obj->deref();
    return 0;
}

static int lookup_method(lua_State *L)
{
    int args = lua_gettop(L);
    if (args != 2)
    {
        lua_pushfstring(L,
            "lookup_method: invalid number of arguments "
            "(exprected 2; received: %d)", args );
        lua_error(L);
    }
    if (!lua_isuserdata(L, -2))
    {
        lua_pushstring(L, "lookup_method: first argument must be userdata");
        lua_error(L);
    }
    if (!lua_isstring(L, -1))
    {
        lua_pushstring(L, "lookup_method: second argument must be string");
        lua_error(L);
    }

    /* Look up method using object reference and method name */
    LuaObj *obj = *(LuaObj**)lua_touserdata(L, -2);
    const char *name = lua_tostring(L, -1);

    LuaMethodBase *meth = obj->get_method(name);
    if (meth == NULL)
    {
        lua_pushfstring(L,
            "lookup_method: no method named \"%s\" declared", name);
        lua_error(L);
    }

    lua_pushlightuserdata(L, (void*)obj);
    lua_pushlightuserdata(L, (void*)meth);
    lua_pushcclosure(L, invoke_method, 2);
    return 1;
}

LuaMethodBase *LuaObj::get_method(const std::string &name) const
{
    std::map<std::string, LuaMethodBase *>::const_iterator it;
    it = methods.find(name);
    if (it == methods.end()) return NULL;
    return it->second;
}

LuaObj::LuaObj() : refcount(0)
{
}

LuaObj::~LuaObj()
{
    for ( MethodMap::const_iterator it = methods.begin();
          it != methods.end(); ++it )
    {
        delete it->second;
    }
}

void LuaObj::add_method(const std::string &name, LuaMethodBase *method)
{
    MethodMap::iterator it = methods.find(name);
    if (it != methods.end()) delete it->second;
    methods[name] = method;
}

void LuaObj::push(lua_State *L)
{
    *(void**)lua_newuserdata(L, sizeof(void*)) = (void*)this;
    lua_newtable(L);
    lua_pushstring(L, "__index");
    lua_pushcfunction(L, lookup_method);
    lua_rawset(L, -3);
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, free_object);
    lua_rawset(L, -3);
    lua_setmetatable(L, -2);
    refcount += 1;
}

void LuaObj::deref()
{
    refcount -= 1;
    if (refcount <= 0) delete this;
}
