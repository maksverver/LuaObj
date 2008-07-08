#include <string>

template<> inline int get_arg<int>(lua_State *L, int idx)
{
    return lua_tointeger(L, idx);
}

template<> inline float get_arg<float>(lua_State *L, int idx)
{
    return (float)lua_tonumber(L, idx);
}

template<> inline double get_arg<double>(lua_State *L, int idx)
{
    return (double)lua_tonumber(L, idx);
}

template<> inline const char *get_arg<const char *>(lua_State *L, int idx)
{
    return lua_tostring(L, idx);
}

template<> inline std::string get_arg<std::string>(lua_State *L, int idx)
{
    size_t len;
    const char *data;
    data = lua_tolstring(L, idx, &len);
    return std::string(data, len);
}

template<> inline bool get_arg<bool>(lua_State *L, int idx)
{
    return lua_toboolean(L, idx);
}

