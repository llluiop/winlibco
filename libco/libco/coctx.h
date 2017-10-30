#pragma once

struct Coctx
{
	void* reg[8];
	int size;
	char* sp;
};

bool coctx_init(Coctx*);