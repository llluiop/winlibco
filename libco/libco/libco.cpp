// libco.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "libco.h"
#include "coctx.h"
#include <mutex>

thread_local LibRoutine librt;
std::once_flag flag;

void Cfn(CoRoutine* co)
{
	if (co->f)
	{
		co->f();
	}


	co->end = 1;
	yield_env(&librt);
}

void swap(CoRoutine* cur, CoRoutine* pending)
{
	coctx_swap(&cur->coctx, &pending->coctx);
}

StackMem* alloc_stackmem(int size)
{
	StackMem* mem = new StackMem;
	mem->size = size;
	mem->stack_buffer = new char[size];
	mem->stack_bp = mem->stack_buffer + size;

	return mem;
}

CoRoutine* create_env(const RoutineAttr* attr, std::function<void()> f)
{
	CoRoutine* co = new CoRoutine;
	co->f = f;
	co->start = 0;
	co->end = 0;
	co->shared = false;

	coctx_init(&co->coctx);

	int size = attr == nullptr ? 10 * 1024 : attr->size;
	co->mem = alloc_stackmem(size);

	co->coctx.size = size;
	co->coctx.sp = co->mem->stack_buffer;

	co->rt = &librt;

	return co;
}



DLL_EXPORT int create(const CoRoutine** co, const RoutineAttr* attr, std::function<void()> f)
{
	std::call_once(flag, []() {
		auto rt = create_env(nullptr, nullptr);
		rt->main = true;
		
		coctx_init(&rt->coctx);

		librt.stack[0] = rt;
		++librt.size;
	});
	
	*co = create_env(attr, f);
	 
	return 0;
}


DLL_EXPORT void resume( CoRoutine* co)
{
	auto co_now = librt.stack[librt.size - 1];
	if (co_now->start != 1)
	{
		co_now->start = 1;
		coctx_make(&co->coctx, (CoRoutinePfn)Cfn, Coctx_param{ co, nullptr });
	}

	librt.stack[librt.size++] = co;
}

DLL_EXPORT void yield( CoRoutine* co)
{
	yield_env(co->rt);

}

DLL_EXPORT void yield_env(LibRoutine * rt)
{
	auto cur = rt->stack[rt->size - 1];
	auto last = rt->stack[rt->size - 2];

	rt->size--;

	swap(cur, last);
}

DLL_EXPORT void release( CoRoutine * co)
{
	
}



