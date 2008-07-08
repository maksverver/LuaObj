#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include "LuaObj.h"

class Test : public LuaObj
{
public:
    Test(lua_State *L);
    int foo();
    int bar(int);
    int baz(int, int);
    void quux();
};

#endif /* ndef TEST_H_INCLUDED */

