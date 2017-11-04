#pragma once

#include <functional>


#ifdef LIBCO_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

struct Coctx
{
	void* reg[8];
	int size;
	char* sp;
};

struct Coctx_param
{
	void* s1;
	void* s2;
};


//manager all the routines
struct CoRoutine;
struct LibRoutine
{
	CoRoutine* stack[128];
	int size;
};

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





extern "C"
{
	DLL_EXPORT int create(CoRoutine** co,const RoutineAttr* attr, std::function<void()> f);
	DLL_EXPORT void resume( CoRoutine* co);
	DLL_EXPORT void yield(CoRoutine* co);
	DLL_EXPORT void yield_env(LibRoutine* rt);
	DLL_EXPORT void release( CoRoutine* co);
}