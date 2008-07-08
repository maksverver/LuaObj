#include <lua.hpp>
#include <cstdio>
#include "Test.h"

using std::printf;

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        printf("Missing argument: script file name.\n");
        return 1;
    }

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_loadfile(L, argv[1]) != 0)
    {
        printf("Could not load script \"%s\"!\n", argv[1]);
        return 1;
    }

    lua_newtable(L);
    for (int i = 1; i <= 5; i++)
    {
        lua_pushnumber(L, i);
        lua_pushnumber(L, i*2);
        lua_rawset(L, -3);
    }
    lua_setglobal(L, "testtable");
    (new Test())->push(L);
    lua_setglobal(L, "start");

    if (lua_pcall(L, 0, 0, 0) != 0)
    {
        const char *msg = lua_tostring(L, -1);
        printf( "Script execution failed!\n%s\n",
                 msg ? msg : "(no error message)" );
        return 1;
    }

    lua_close(L);

    return 0;
}
