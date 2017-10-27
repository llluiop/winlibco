// libco.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "libco.h"
#include <mutex>

thread_local LibRoutine librt;
std::once_flag flag;

DLL_EXPORT int create(const CoRoutine** co, const RoutineAttr& attr, std::function<void()> f)
{
	std::call_once(flag, []() {
		CoRoutine rt;
		librt.cot[0] = rt;
		++librt.size;
	});
	
	*co = create_env(attr, f);

	return 0;
}


DLL_EXPORT void resume(const CoRoutine* co)
{

}

DLL_EXPORT void yield(const CoRoutine* co)
{

}

DLL_EXPORT void release(const CoRoutine * co)
{
	
}


CoRoutine* create_env(const RoutineAttr& attr, std::function<void()> f)
{
	CoRoutine* co = new CoRoutine;

	return co;
}