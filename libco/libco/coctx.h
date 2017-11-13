#pragma once

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

typedef void(*CoRoutinePfn)(Coctx*);

bool coctx_init(Coctx*);
void coctx_make(Coctx*, CoRoutinePfn pfn, void* s1);