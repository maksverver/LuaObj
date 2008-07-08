
// 0 arguments, returning void
template<class C>
class LuaMethodV0 : public LuaMethodBase
{
    typedef void (C::*M)();
    M method;
public:
    LuaMethodV0(M m) : method(m) { };
    int invoke(lua_State *L, void *obj)
    {
        (((C*)obj)->*method)();
        return 0;
    }
};

template<class C>
inline LuaMethodBase *new_method(void (C::*m)())
{
    return new LuaMethodV0<C>(m);
}

// 0 arguments, returning void
template<class C, class R>
struct LuaMethodR0 : public LuaMethodBase
{
    typedef R (C::*M)();
    M method;
public:
    LuaMethodR0(M m) : method(m) { };
    int invoke(lua_State *L, void *obj)
    {
        return push_res(L, (((C*)obj)->*method)() );
    }
};

template<class C, class R>
inline LuaMethodBase *new_method(R (C::*m)())
{
    return new LuaMethodR0<C, R>(m);
}

// 1 arguments, returning void
template<class C, class A1>
class LuaMethodV1 : public LuaMethodBase
{
    typedef void (C::*M)(A1);
    M method;
public:
    LuaMethodV1(M m) : method(m) { };
    int invoke(lua_State *L, void *obj)
    {
        (((C*)obj)->*method)(get_arg<A1>(L, 2));
        return 0;
    }
};

template<class C, class A1>
inline LuaMethodBase *new_method(void (C::*m)(A1))
{
    return new LuaMethodV1<C, A1>(m);
}

// 1 arguments, returning non-void
template<class C, class R, class A1>
struct LuaMethodR1 : public LuaMethodBase
{
    typedef R (C::*M)(A1);
    M method;
public:
    LuaMethodR1(M m) : method(m) { };
    int invoke(lua_State *L, void *obj)
    {
        return push_res(L, (((C*)obj)->*method)(get_arg<A1>(L, 2)) );
    }
};

template<class C, class R, class A1>
inline LuaMethodBase *new_method(R (C::*m)(A1))
{
    return new LuaMethodR1<C, R, A1>(m);
}


// 2 arguments, returning void
template<class C, class A1, class A2>
class LuaMethodV2 : public LuaMethodBase
{
    typedef void (C::*M)(A1, A2);
    M method;
public:
    LuaMethodV2(M m) : method(m) { };
    int invoke(lua_State *L, void *obj)
    {
        (((C*)obj)->*method)(get_arg<A1>(L, 2), get_arg<A2>(L, 3));
        return 0;
    }
};

template<class C, class A1, class A2>
inline LuaMethodBase *new_method(void (C::*m)(A1, A2))
{
    return new LuaMethodV2<C, A1, A2>(m);
}

// 2 arguments, returning non-void
template<class C, class R, class A1, class A2>
struct LuaMethodR2 : public LuaMethodBase
{
    typedef R (C::*M)(A1, A2);
    M method;
public:
    LuaMethodR2(M m) : method(m) { };
    int invoke(lua_State *L, void *obj)
    {
        return push_res(L, (((C*)obj)->*method)( get_arg<A1>(L, 2),
                                                 get_arg<A2>(L, 3) ));
    }
};

template<class C, class R, class A1, class A2>
inline LuaMethodBase *new_method(R (C::*m)(A1, A2))
{
    return new LuaMethodR2<C, R, A1, A2>(m);
}
