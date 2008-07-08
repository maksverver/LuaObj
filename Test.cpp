#include "Test.h"

Test::Test(lua_State *L) : LuaObj(L)
{
    add_method("foo", new_method(&Test::foo));
    add_method("quux", new_method(&Test::quux));
    add_method("bar", new_method(&Test::bar));
    add_method("baz", new_method(&Test::baz));
}

int Test::foo()
{
    return 666;
}

int Test::bar(int a)
{
    return a + 1;
}

int Test::baz(int a, int b)
{
    return a + b;
}

#include <cstdio>
void Test::quux()
{
    std::printf("Quux called!\n");
}

