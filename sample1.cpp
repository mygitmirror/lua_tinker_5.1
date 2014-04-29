// sample1.cpp : C++ �� Lua ��ȣ���� �Լ� ������ �˾ƺ���.
//

#include <iostream>

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
};

#include "lua_tinker.h"
class A {
public:
    int a;
};

class B {
public:
    int b;
};

int test_arg8(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8)
{
    return arg1+arg2+arg3+arg4+arg5+arg6+arg7+arg8;
}

int test_arg7(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7)
{
    return arg1+arg2+arg3+arg4+arg5+arg6+arg7;
}

int test_arg6(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    return arg1+arg2+arg3+arg4+arg5+arg6;
}

int test_ref_arg(const A& a, const B& b)
{
    return a.a + b.b;
}

int cpp_func(int arg1, int arg2)
{
	return arg1 + arg2;
}

int main()
{
	// Lua �� �ʱ�ȭ �Ѵ�.
	lua_State* L = lua_open();

	// Lua �⺻ �Լ����� �ε��Ѵ�.- print() ���
	luaopen_base(L);

	lua_tinker::class_add<A>(L, "A");
	lua_tinker::class_mem<A>(L, "a", &A::a);

	lua_tinker::class_add<B>(L, "B");
	lua_tinker::class_mem<B>(L, "b", &B::b);

    A inst_a;
    inst_a.a = 11;
    const A& ref_a = inst_a;

    B inst_b;
    inst_b.b = 11;
    const B& ref_b = inst_b;

	// LuaTinker �� �̿��ؼ� �Լ��� ����Ѵ�.
	lua_tinker::def(L, "cpp_func", cpp_func);
	lua_tinker::def(L, "test_ref_arg", test_ref_arg);
	lua_tinker::def(L, "test_arg6", test_arg6);
	lua_tinker::def(L, "test_arg7", test_arg7);
	lua_tinker::def(L, "test_arg8", test_arg8);

	// sample1.lua ������ �ε�/�����Ѵ�.
	lua_tinker::dofile(L, "sample1.lua");

	// sample1.lua �� �Լ��� ȣ���Ѵ�.
	int result = lua_tinker::call<int>(L, "lua_func", 3, 4);

	// lua_func(3,4) �� ����� ���
	printf("lua_func(3,4) = %d\n", result);

    result = lua_tinker::call<int>(L, "lua_test_ref_arg", ref_a, ref_b);
	printf("lua_test_ref(ref_a,ref_b) = %d\n", result);

	// ���α׷� ����
	lua_close(L);

	return 0;
}
