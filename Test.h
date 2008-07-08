#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include "LuaObj.h"
#include <string>

class Test : public LuaObj
{
    std::string msg;

public:
    Test(const char *str = "message");
    int foo();
    int bar(int);
    int baz(int, int);
    void quux();
    void setMsg(std::string s);
    std::string getMsg();
    LuaObj *gimme();
    void test(LuaObj *obj);
};

#endif /* ndef TEST_H_INCLUDED */

