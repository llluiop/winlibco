#pragma once

#include <functional>

#ifdef LIBCO_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

struct StackMem
{
	int size;
	char* stack_buffer;
	char* stack_bp;
};

//represent a routine
struct CoRoutine
{
	std::function<void()> f;
	
	char* stack_sp;
	int save_size;
	char* stack_buffer;

	char start;
	char end;
	char shared;

	bool main;

	Coctx coctx;

	StackMem* mem;

	LibRoutine* rt;
};

// RoutineAttr
struct RoutineAttr
{
	int size;
};

//manager all the routines
struct LibRoutine
{
	CoRoutine* stack[128];
	int size;
};



extern "C"
{
	DLL_EXPORT int create(CoRoutine** co, const RoutineAttr* attr, std::function<void()> f);
	DLL_EXPORT void resume( CoRoutine* co);
	DLL_EXPORT void yield( CoRoutine* co);
	DLL_EXPORT void release( CoRoutine* co);
}