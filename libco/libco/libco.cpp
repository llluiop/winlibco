// libco.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "libco.h"
#include <mutex>

thread_local LibRoutine librt;
std::once_flag flag;

DLL_EXPORT int create(const CoRoutine** co, const RoutineAttr& attr)
{
	std::call_once(flag, []() {
		CoRoutine rt;
		librt.cot[0] = rt;
		++librt.size;
	});
	
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
