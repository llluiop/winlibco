#pragma once

#include <functional>

#ifdef LIBCO_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

//represent a routine
struct CoRoutine
{
	std::function<void()> f;
	int eip;
	int ebp;
	int esp;
	int stack;
	int size;
};

// RoutineAttr
struct RoutineAttr
{
	int size;
};

//manager all the routines
struct LibRoutine
{
	CoRoutine cot[128];
	int size;
};

extern "C"
{
	DLL_EXPORT int create(CoRoutine** co, const RoutineAttr& attr);
	DLL_EXPORT void resume(const CoRoutine* co);
	DLL_EXPORT void yield(const CoRoutine* co);
	DLL_EXPORT void release(const CoRoutine* co);
}