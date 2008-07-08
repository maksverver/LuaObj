#include <string>

template<> inline int push_res<int>(lua_State *L, int const &val)
{
    lua_pushnumber(L, val);
    return 1;
}

template<> inline int push_res<float>(lua_State *L, float const &val)
{
    lua_pushnumber(L, val);
    return 1;
}

template<> inline int push_res<double>(lua_State *L, double const &val)
{
    lua_pushnumber(L, val);
    return 1;
}

template<> inline int push_res<char const *>(lua_State *L, char const *const &val)
{
    lua_pushstring(L, val);
    return 1;
}

template<> inline int push_res<std::string>(lua_State *L, std::string const &val)
{
    lua_pushlstring(L, val.data(), val.size());
    return 1;
}

template<> inline int push_res<bool>(lua_State *L, bool const &val)
{
    lua_pushboolean(L, val);
    return 1;
}
