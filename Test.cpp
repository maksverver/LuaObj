#include "Test.h"
#include <cstdio>

Test::Test(const char *str) : msg(str)
{
    add_method("foo", new_method(&Test::foo));
    add_method("quux", new_method(&Test::quux));
    add_method("bar", new_method(&Test::bar));
    add_method("baz", new_method(&Test::baz));
    add_method("gimme", new_method(&Test::gimme));
    add_method("getMsg", new_method(&Test::getMsg));
    add_method("setMsg", new_method(&Test::setMsg));
    add_method("test", new_method(&Test::test));
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

void Test::quux()
{
    std::printf("Quux called!\n");
}

void Test::setMsg(std::string s)
{
    msg = s;
}

std::string Test::getMsg()
{
    return msg;
}

LuaObj *Test::gimme()
{
    return new Test("nieuw!");
}

void Test::test(LuaObj *_obj)
{
    Test *obj = dynamic_cast<Test*>(_obj);
    if (obj != NULL) std::printf("%s => %s\n", msg.c_str(), obj->msg.c_str());
}
